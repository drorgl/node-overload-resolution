#include "overload_resolution.h"

#include <algorithm>
#include <numeric>

#include "async_worker.h"
#include <tracer.h>

#include "function_arguments.h"
#include "overload_resolution_types.h"
#include "function_rank_cache.h"


static void Log(LogLevel level, std::string &&message) {
	if (tracer::log_level <= level) {
		tracer::Log("overload_resolution", level, std::move(message));
	}
}

static void Log(LogLevel level, std::function<std::string()> message) {
	if (tracer::log_level <= level) {
		tracer::Log("overload_resolution", level, message);
	}
}


overload_resolution::overload_resolution() {
	Log( LogLevel::DEBUG, "initializing");
	Log(LogLevel::DEBUG, []() {return "primitive types " + tracer::join(or ::type_system::primitive_types, [](const std::string &s) {return s; }, ", "); });
	Log(LogLevel::DEBUG, []() {return "convertible primitive types " + tracer::join(or ::type_system::convertible_primitive_types, [](const std::string &s) {return s; }, ", "); });
}

overload_resolution::~overload_resolution() {
	Log( LogLevel::DEBUG, "terminating");
	_type_system.reset();
	_function_cache.reset();

#ifdef DEBUG
	_CrtDumpMemoryLeaks();
#endif
}

void overload_resolution::LogDebug(std::function<std::string()> message) {
	Log(LogLevel::DEBUG, message);
}
void overload_resolution::LogWarn(std::function<std::string()> message) {
	Log(LogLevel::WARN, message);
}


void overload_resolution::add_type_alias(std::string alias, std::string type) {
	assert(!alias.empty() && "alias can not be empty");
	assert(!type.empty() && "alias type can not be empty");
	Log(LogLevel::DEBUG, [&alias, &type]() {return "adding alias " + alias + " for " + type; });
	_type_system.add_type_alias(alias, type);
}




bool overload_resolution::validate_type_registrations() {
	return _type_system.validate_type_registrations();
}


void overload_resolution::addOverload(const std::string ns, const std::string className, const std::string name, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	Log( LogLevel::DEBUG, [&ns, &className, &name, &arguments]() {
		return "add overload " + ns + "::" + className + "::" + name + "(" + 
			tracer::join(arguments, [](const std::shared_ptr<overload_info> oi) {return oi->type + " " + oi->parameterName; },", ") 
			+ ")"; 
	});
	std::string functionName = "+" + name;

	_type_system.create_function_store(ns, className, functionName);
	
	//add function to functions collection
	auto f = std::make_shared<o_r_function>();
	f->function = callback;
	f->functionName = functionName;
	f->className = className;
	f->parameters = arguments;
	f->is_constructor = false;
	f->is_static = false;
	_type_system.add_overload(ns, className, functionName, f);
}

void overload_resolution::addStaticOverload(const std::string ns, const std::string className, const std::string name, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	Log( LogLevel::DEBUG, [&ns, &className, &name, &arguments]() {
		return "add static overload " + ns + "::" + className + "::" + name + "(" +
			tracer::join(arguments, [](const std::shared_ptr<overload_info> oi) {return oi->type + " " + oi->parameterName; }, ", ")
			+ ")";
	});
	std::string functionName = "-" + name;
	_type_system.create_function_store(ns, className, functionName);

	//add function to functions collection
	auto f = std::make_shared<o_r_function>();
	f->function = callback;
	f->functionName = functionName;
	f->className = className;
	f->parameters = arguments;
	f->is_constructor = false;
	f->is_static = true;
	_type_system.add_overload(ns, className, functionName, f);
}

void overload_resolution::addOverloadConstructor(const std::string ns, const std::string className, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	Log( LogLevel::DEBUG, [&ns, &className, &arguments]() {
		return "add constructor overload " + ns + "::" + className + "::" + "(" +
			tracer::join(arguments, [](const std::shared_ptr<overload_info> oi) {return oi->type + " " + oi->parameterName; }, ", ")
			+ ")";
	});
	//add ::constructor to function name, to avoid confusion if the class has classname as a function
	std::string functionName = "%" + className;
	_type_system.create_function_store(ns, className, functionName);

	//add function to functions collection
	auto f = std::make_shared<o_r_function>();
	f->function = callback;
	f->functionName = functionName;
	f->className = className;
	f->parameters = arguments;
	f->is_constructor = true;
	f->is_static = false;
	_type_system.add_overload(ns, className, functionName, f);
}


int overload_resolution::MatchOverload(std::vector<std::string> &classNames, std::shared_ptr<o_r_function> func, or::function_arguments &fargs) {
	//TODO: add parameters + static/constructor to log
	Log( LogLevel::TRACE, [&func]() {return "matching overload for " + func->className + "::" + func->functionName; });
	int parameterLength = (std::max)((int)func->parameters.size(), fargs.length());
	int rank = 0;

	//in case there are no parameters to this function, its always a possible candidate, though low priority
	if ((func->parameters.size() == 0) && (fargs.length() == 0)) {
		Log(LogLevel::TRACE, [&func]() {return "function has no parameters, no parameters supplied"; });
		return std::pow(2, 10);
	}
	else if ((func->parameters.size() == 0)) {
		Log( LogLevel::TRACE, [&func]() {return "function has no parameters, low priority candidate"; });
		return 1;
	}

	if ((int)func->parameters.size() == fargs.length()) {
		rank += 1;
	}

	//check conversion of prototype types, give higher score to closer conversions, don't check if only one className exists
	if (!func->className.empty() && (std::size(classNames) > 1)) {
		auto classNameIndex = std::find(std::begin(classNames), std::end(classNames), func->className) - std::begin(classNames);
		if (classNameIndex < std::size(classNames)) {
			rank += std::size(classNames) - classNameIndex;
		}
	}

	for (auto i = 0; i < parameterLength; i++) {
		int local_rank = 0;
		//auto iparam = (fargs.length() > i) ? fargs info[i] : Nan::Undefined();
		auto iparam_type = fargs.get_type(i);// determineType(iparam);
		auto fparam = (func->parameters.size() > i) ? func->parameters.at(i) : nullptr;

		//if a function parameer is not present, this is an extra parameter which should be ignored. a function is considered valid but on a lower rank
		if (fparam == nullptr) {
			Log( LogLevel::TRACE, [&i]() {return "extra unused parameter passed at index " + std::to_string(i); });
			break;
		}
		
		//check if the function parameter and info parameter types are the same
		auto fparam_normalized_type = _type_system.normalize_types(fparam->type);
		auto fparam_aliases = _type_system.drill_type_aliases(fparam->type);

		

		if (fparam_normalized_type == iparam_type) {
			Log( LogLevel::TRACE, [&fparam, &fparam_normalized_type, &iparam_type]() {return "exact type matched " + fparam_normalized_type + "(" + fparam->type + ") == " + iparam_type;  });
			local_rank = std::pow(2, 10);
		}
		
		//check if the function parameter and info parameter types are convertible
		//make sure undefined was actually passed so conversion to boolean won't be used
		
		else if (fargs.length() > i && (fargs.is_convertible_to(i,fparam_aliases))) {
			Log(LogLevel::TRACE, [&fparam_aliases]() {return "type is convertible to " + fparam_aliases; });
			//if its convertible to boolean, it should be a valid function, but not on any priority
			if (iparam_type == "Undefined" || fargs.is_array(i)) {
				local_rank = 1;
			}
			else if (fparam_aliases == "Boolean") {
				local_rank = 2;
			}
			else {
				local_rank = std::pow(2, 4);
			}
		}
		//if this is undefined AND a default value is supplied, this is valid and gets one point
		else if (iparam_type == "Undefined" && ((!fparam->defaultValue.IsEmpty() && !(Nan::New(fparam->defaultValue)->IsUndefined())))) {
			Log(LogLevel::TRACE, [&i]() {return "no parameter is available but a default value is supplied at index " + i; });
			local_rank = 3;
		}
		//if this is the last parameter AND its a function, this is valid but no score
		else if (iparam_type == "Function" && (i == (func->parameters.size() - 1)) && fparam_normalized_type == "Function") {
			Log(LogLevel::TRACE, [&i]() {return "a function is available in the last position, which could mean its an async call, ignore it"; });
			local_rank = 1;
		}
		//otherwise, its not valid
		else {
			Log(LogLevel::TRACE, [&i]() {return "no matching lower priority parameter is available, this overload is not valid"; });
			return -1;
		}

		//TODO: how to handle array types?

		//TODO: check interface/structures?


		//if any of the function parameter is not convertible, return -1;

		if (local_rank > -1) {
			rank += local_rank;
		}
		else {
			Log( LogLevel::TRACE, [&func]() {return "overload for " + func->className + "::" + func->functionName + " does not match"; });
			return -1;
		}
	}

	return rank;
}

void overload_resolution::execute_overload(const std::string &ns, std::vector<std::string> &classNames, const std::string &name, std::shared_ptr<o_r_function> function, Nan::NAN_METHOD_ARGS_TYPE info) {

	auto parametersLength = (std::max)(info.Length(), (int)function->parameters.size());
	std::vector<v8::Local<v8::Value>> info_params;
	for (auto i = 0; i < parametersLength; i++) {
		if (info.Length() > i && !info[i]->IsUndefined()) {
			info_params.push_back(info[i]);
		}
		else if (function->parameters.size() > i) {
			info_params.push_back(Nan::New(function->parameters[i]->defaultValue));
		}
		else {
			info_params.push_back(Nan::Undefined());
		}
	}




	//handle async callbacks:
	// if last parameter is a function not part of the best overload function, it means an async was requested
	// in this case, cache all the function parameters, create an async wrapper, execute the function in the threadpool
	// post process the returned values as regular functions (both SetReturnValue and function return value)

	//process returned values, check if SetReturnValue was called, if so, make sure to use the passed value, otherwise, proceed as normal



	std::shared_ptr< or ::value_converter_base> this_converter;

	if (function->className != "") {
		auto this_type = _type_system.get_type(function->className);
		if (this_type != nullptr) {
			this_converter = this_type->value_converter;
		}
		else {
			Log(LogLevel::WARN, [&function]() {return "type " + function->className + " was not defined, no converter available"; });
		}
	}


	//check if the call is async by checking if there is additional parameter which is a function
	//if so, execute it as an async call
	if (!function->is_constructor &&  info.Length() > function->parameters.size()
		&& info[function->parameters.size()]->IsFunction()) {
		Log(LogLevel::DEBUG, [&ns, &classNames, &name]() {return "function " + ns + "::(" + tracer::join(classNames, "/") + ")::" + name + " was requested async execution"; });



		auto async_processed_info = std::make_shared< or ::FunctionCallbackInfo<v8::Value>>(info, info_params, function->parameters, this_converter, true);
		auto async_cb = std::make_shared< or ::Callback>(info[function->parameters.size()].As<v8::Function>());
		async_cb->is_async = true;
		queue_async_polyfunction(function->function, async_processed_info, async_cb);



		return;
	}


	auto processed_info = std::make_shared< or ::FunctionCallbackInfo<v8::Value>>(info, info_params, function->parameters, this_converter, false);
	Log(LogLevel::DEBUG, [&ns, &classNames, &name]() {return "function " + ns + "::(" + tracer::join(classNames, "/") + ")::" + name + " was requested sync execution"; });
	try {
		//execute the callback function
		function->function(*processed_info);

		//execute post process on function callback info
		processed_info->post_process();

		return;
	}
	catch (std::exception &std_exception) {
		std::string errDetail = "error executing " + name + " " + std_exception.what();
		Log(LogLevel::ERROR, [&errDetail]() {return errDetail; });
		return Nan::ThrowError(errDetail.c_str());
	}
}

void overload_resolution::executeBestOverload(const std::string &ns, std::vector<std::string> &classNames, const std::string &name, Nan::NAN_METHOD_ARGS_TYPE info) {
	//TODO: add arguments to the log
	Log( LogLevel::DEBUG, [&ns, &classNames, &name, &info]() {
		std::string arguments = "";
		for (auto i = 0; i < info.Length(); i++) {
			if (i > 0) {
				arguments += ", ";
			}
			arguments += *Nan::Utf8String(info[i]->ToDetailString());
		}
		return "executing best overload for " + ns + "::(" + tracer::join(classNames, "/" ) + ")::" + name + "(" + arguments +  ")"; 
	});


	or ::function_arguments func_args(_type_system, info);

	auto cached = _function_cache.get_function(ns, classNames, name, func_args);
	if (auto cachedOverloadFunction = cached.lock()) {
		return execute_overload(ns, classNames, name, cachedOverloadFunction, info);
	}

	std::vector<std::pair<int,std::weak_ptr< o_r_function>>> candidates;

	std::vector < std::shared_ptr< o_r_class>> classes;

	_type_system.get_classes(ns, classNames, classes);


	//TODO: classNames are ordered by class inheritance, from derived to base
	// need to iterate over them and if two functions have the same rank, give priority to derived.

	if (classes.size() == 0) {

		std::string errclass = "";
		if (ns != "") {
			errclass = ns;
			errclass += "::";
		}

		errclass += "(" + std::accumulate(std::begin(classNames), std::end(classNames), std::string(), [](std::string &ss, std::string &s) {return ss.empty() ? s : ss + "," + s; }) + ")";


		if (name != "") {
			errclass += "::";
			errclass += name;
		}

		errclass = "no overload for namespace or class " + errclass;
		Log( LogLevel::ERROR, [&errclass]() {return errclass; });
		return Nan::ThrowError(errclass.c_str());
	}

	
	std::vector<std::shared_ptr< o_r_function>> implementations;

	//copy all class functions by name from all descendant classes
	_type_system.get_functions(ns, classNames, name, implementations);


	

	//auto func_args_key = func_args.get_type_key();


	for (auto i = 0; i < implementations.size(); i++) {
		auto check = implementations[i];
		assert(( check->functionName == name ) && "function name must match");
		if (check->functionName != name) {
			Log( LogLevel::ERROR, [&check, &name]() {return "function names do not match " + check->functionName + " and " + name; });
		}

		//check if the function parameter count equals the info parameters count, give a point in favor but only if reached maximum points
		auto rank = MatchOverload(classNames, check, func_args);
		if (rank > 0) {
			candidates.push_back(std::pair<int,std::weak_ptr< o_r_function>>(rank, check));
		}

	}

	Log( LogLevel::TRACE, [&ns, &classNames, &name,&candidates]() {return "function " + ns + "::(" + tracer::join(classNames, "/") + ")::" + name + " has " +std::to_string( candidates.size()) + " valid candidates"; });

	//log the best one
	//if none found, throw an exception that no overload satisfies the supplied parameters and the best overloaded candidate
	if (candidates.size() > 0) {
		auto bestOverload = std::max_element(candidates.begin(), candidates.end(), [](std::pair<int,std::weak_ptr< o_r_function>> a, std::pair<int,std::weak_ptr< o_r_function>> b) {return a.first < b.first; });
		if (auto bestOverloadFunction = bestOverload->second.lock()) { // Has to be copied into a shared_ptr before usage
			Log( LogLevel::DEBUG, [&bestOverloadFunction,&ns, &classNames, &name]() {return "best candidate is " + ns + "::(" + tracer::join(classNames, "/") + ")::" + name + "(" + tracer::join(bestOverloadFunction->parameters, [](const std::shared_ptr<overload_info> oi) {return oi->type + " " + oi->parameterName; }, ", ") + ")";});

			//cache the best candidate
			_function_cache.cache_function(ns, classNames, name, func_args, bestOverloadFunction);

			//execute the candidate
			return execute_overload(ns, classNames, name, bestOverloadFunction, info);
		}
		else {
			assert(false && "overloaded function was removed, this error most likely means a buffer overflow");
			Log( LogLevel::ERROR, []() {return "overloaded function was removed, this error most likely means a buffer overflow"; });
		}
		
	}

	//TODO: add details to this log entry
	Log( LogLevel::ERROR, []() {return "no overload fulfills the parameters passed"; });

	return Nan::ThrowError("no overload fulfills the parameters passed");
}


Nan::NAN_METHOD_RETURN_TYPE overload_resolution::execute(const std::string name_space, Nan::NAN_METHOD_ARGS_TYPE info){
	//TODO: add info to log entry
	Log( LogLevel::TRACE, [&name_space]() {return "executing in namespace " + name_space; });

	bool isConstructorCall = info.IsConstructCall();

	std::string functionName = *Nan::Utf8String(info.Callee()->GetName());
	std::string className = "";
	bool isStatic = false;

	if (info.This()->IsFunction()) {
		//static
		className = *Nan::Utf8String(info.This().As<v8::Function>()->GetName());
		isStatic = true;
	}
	else {
		//member
		className = *Nan::Utf8String(info.This()->GetConstructorName());
	}

	//if the className is Object, it means its not a member
	if (className == "Object") {
		className = "";
	}
	
	
	if (isStatic) {
		functionName = "-" + functionName;
	}else if (isConstructorCall) {
		functionName = "%" + functionName;
	}
	else {
		//if not static or constructor, its a member
		functionName = "+" + functionName;
	}

	std::vector<std::string> prototypeClassChain;

	//if call is static or constructor, only execute on class itself
	if (isStatic || isConstructorCall) {
		prototypeClassChain.push_back(className);
	}
	else {
		_type_system.getPrototypeChain(info.This(), prototypeClassChain);
	}

	
	if (prototypeClassChain.size() == 0) {
		//for functions without prototype chain, it means they are in the global namespace
		prototypeClassChain.push_back("");
	}

	Log( LogLevel::DEBUG, [&name_space, &prototypeClassChain, &functionName]() {return "executing " + name_space + "::(" + tracer::join(prototypeClassChain, "/") + ")" + functionName; });

	return executeBestOverload(name_space, prototypeClassChain, functionName, info);
}

