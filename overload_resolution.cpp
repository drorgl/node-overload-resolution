#include "overload_resolution.h"

std::set<std::string> overload_resolution::_convertible_primitive_types = {"Number","String","Boolean"};

std::set<std::string> overload_resolution::_primitive_types = {"Number","String","Boolean","Date","Buffer","Function","Map","Set","Null","Promise","Proxy","RegExp"};


overload_info::overload_info(const char * parameterName, const char * type, v8::Local<v8::Value> defaultValue) {
	this->parameterName = parameterName;
	this->type = type;
	this->defaultValue.Reset(defaultValue);
}

overload_resolution::overload_resolution() {

}


void overload_resolution::register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const char * ns, const char * name) {
	assert(_types.count(name) == 0 && "type name already exists");

	auto ot = std::make_shared< object_type>();
	ot->function_template .Reset(functionTemplate);
	ot->ns = ns;
	ot->name = name;
	_types[name] = ot;
}

bool overload_resolution::validate_type_registrations() {
	for (std::map<std::string, o_r_namespace>::iterator ns = std::begin(_namespaces); ns != std::end(_namespaces); ns++) {
		//for each namespace
		for (std::map<std::string, std::shared_ptr< o_r_class>>::iterator cls = std::begin(ns->second.classes); cls != std::end(ns->second.classes); cls++) {
			//for each class 
			for (std::map<std::string, std::vector<std::shared_ptr< o_r_function>>>::iterator fn = std::begin(cls->second->functions); fn != std::end(cls->second->functions); fn++) {
				//for each function
				for (std::vector<std::shared_ptr< o_r_function>>::iterator fnoverload = std::begin(fn->second); fnoverload != std::end(fn->second); fnoverload++) {
					//for each function overload
					for (std::vector<std::shared_ptr<overload_info>>::iterator olinfo = std::begin(fnoverload->get()->parameters); olinfo != std::end(fnoverload->get()->parameters); olinfo++) {
						//for each overload parameter
						auto type = olinfo->get()->type;

						if ((_types.count(type) == 0 ) &&
							(!_structured_factory.has_type(type)) && 
							(_primitive_types.count(type) == 0)
							//TODO: add handling for "generic" arrays (??)
							)
						{
							//printf("type not found: %s", olinfo->get()->type);
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

void overload_resolution::addOverload(const char * ns, const char * className, const char * name, std::vector<std::shared_ptr<overload_info>> arguments, Nan::FunctionCallback callback) {
	//check if namespace exists, if not, create
	if (!_namespaces.count(ns)) {
		_namespaces[ns] = o_r_namespace();
		_namespaces[ns].name = ns;
	}

	//check if class exists, if not, create
	if (!_namespaces[ns].classes.count(className)) {
		_namespaces[ns].classes[className] = std::make_shared<o_r_class>();
		_namespaces[ns].classes[className]->className = className;
	}
	
	//check functions collection exists, if not, create
	if (!_namespaces[ns].classes[className]->functions.count(name)) {
		_namespaces[ns].classes[className]->functions[name] = std::vector<std::shared_ptr<o_r_function>>();
	}
	
	//add function to functions collection
	auto f = std::make_shared<o_r_function>();
	f->function = callback;
	f->functionName = name;
	f->className = className;
	f->parameters = arguments;
	_namespaces[ns].classes[className]->functions[name].push_back(f);
}


const char * overload_resolution::determineType(v8::Local<v8::Value> param) {
	if (param->IsArray()) {
		//TODO: Array of what??
		return "Array";
	}

	if (param->IsArrayBuffer() || param->IsArrayBufferView() || param->IsTypedArray()) {
		return "Buffer";
	}

	if (param->IsBoolean()) {
		return "Boolean";
	}

	if (param->IsDate()) {
		return "Date";
	}

	if (param->IsFunction()) {
		return "Function";
	}

	if (param->IsGeneratorFunction()) {
		return "ConstructorFunction";
	}

	if (param->IsMap()) {
		return "Map";
	}

	if (param->IsSet()) {
		return "Set";
	}

	if (param->IsNull() || param->IsUndefined()) {
		return "Null";
	}

	if (param->IsNumber()) {
		return "Number";
	}

	if (param->IsPromise()) {
		return "Promise";
	}

	if (param->IsProxy()) {
		return "Proxy";
	}

	if (param->IsRegExp()) {
		return "RegExp";
	}

	if (param->IsSymbol()) {
		return "String";
	}

	if (param->IsString()) {
		return "String";
	}

	//first, check the list of registrations, if one of the types match, they are a higher priority

	std::map<std::string, std::shared_ptr<object_type>>::iterator it;

	std::vector<std::shared_ptr<object_type>> alternatives;

	//might be able to optimize with FindInstanceInPrototypeChain
	for (it = _types.begin(); it != _types.end(); it++) {
		if (Nan::New<v8::FunctionTemplate>(it->second-> function_template)->HasInstance(param)) {
			if (strcmp(*Nan::Utf8String(param.As<v8::Object>()->GetConstructorName()), it->second->name) == 0) {
				return it->second->name;
			}
			else {
				alternatives.push_back(it->second);
			}
		}
	}

	if (alternatives.size() > 0) {
		assert(false && "object base was found but not object itself!");
	}

	auto structured = _structured_factory.all();
	for (auto i = 0; i < structured.size(); i++) {
		if (structured[i].second->verify(this,param)){
			return structured[i].first;
		}
	}

	//should not happen, unexpected object was passed!
	if (param->IsObject()) {
		return "Object";
	}

	return "Unknown";
}

bool overload_resolution::isConvertibleTo(v8::Local<v8::Value> param, const char * type) {
	//if converting to number, check that the numbervalue is not nan
	if (type == "Number") {
		if (std::isnan(param->NumberValue())) {
			return false;
		} else{
			return true;
		}
	}

	//if converting to primitive from a primitive, it is possible
	//TODO: not always, a string can be converted to number only if it contains a number
	if (_convertible_primitive_types.count(type) > 0 && _convertible_primitive_types.count(determineType(param)) > 0) {
		return true;
	}

	//check prototypical inheritance
	if (_types.count(type) > 0) {
		if (Nan::New<v8::FunctionTemplate>(_types[type]->function_template)->HasInstance(param)) {
			return true;
		}
	}

	//if converting from anything to boolean, it is possible
	if (type == "Boolean") {
		return true;
	}

	return false;
}

int overload_resolution::MatchOverload(o_r_function *func, Nan::NAN_METHOD_ARGS_TYPE info) {
	int parameterLength = std::max((int)func->parameters.size(), info.Length());
	int rank = 0;

	//in case there are no parameters and a candidate doesn't have any parameters, they most likely meant that overload
	if ((info.Length() == 0) && (func->parameters.size() == 0)) {
		return 1;
	}

	for (auto i = 0; i < parameterLength; i++) {
		int local_rank = 0;
		auto iparam = (info.Length() > i) ? info[i] : Nan::Undefined();
		auto fparam = (func->parameters.size() > i) ? func->parameters.at(i) : nullptr;

		
		

		if (fparam == nullptr) {
			break;
		}
		
		//check if the function parameter and info parameter types are the same
		if (fparam->type == determineType(iparam)) {
			local_rank += 4;
		}
		

		//check if the function parameter and info parameter types are convertible
		//make sure undefined was actually passed so conversion to boolean won't be used
		if ((info.Length() > i) && isConvertibleTo(iparam, fparam->type)) {
			local_rank += 2;
		}

		//TODO: check conversion of prototype types, give higher score to closer conversions, if base/descendant, prefer the exact type.

		//TODO: how to handle array types?

		//TODO: check interface/structures?

		//TODO: check default values - rethink!
		if (! Nan::New<v8::Value>(fparam->defaultValue)->IsUndefined()){
			local_rank += 1;
		}

		//if any of the function parameter is not convertible, return -1;

		if (local_rank > 0) {
			rank += local_rank;
		}
		else {
			return -1;
		}
	}

	return rank;
}

void overload_resolution::getPrototypeChain(v8::Local<v8::Value> param, std::vector<std::string> &chain) {
	if (!param->IsObject()) {
		return;
	}

	auto pobject = param.As<v8::Object>();

	std::string constructorName = *Nan::Utf8String(pobject->GetConstructorName());
	if (constructorName == "Object") {
		return;
	}

	chain.push_back(constructorName);
	getPrototypeChain(pobject->GetPrototype(), chain);
}

void overload_resolution::executeBestOverload(const char * ns, std::vector<std::string> &classNames, const char * name, Nan::NAN_METHOD_ARGS_TYPE info) {
	std::vector<std::pair<int, o_r_function *>> candidates;

	std::vector < std::shared_ptr< o_r_class>> classes;

	for (std::vector<std::string>::iterator cit = classNames.begin(); cit < classNames.end(); cit++) {
		if (_namespaces.count(ns) > 0 && _namespaces[ns].classes.count(*cit) > 0) {
			classes.push_back(_namespaces[ns].classes[*cit]);
		}
	}

	//TODO: classNames are ordered by class inheritance, from derived to base
	// need to iterate over them and if two functions have the same rank, give priority to derived.

	if (classes.size() == 0) {

		std::string errclass = "";
		if (ns != NULL) {
			errclass = ns;
			errclass += "::";
		}

		errclass += "(" + std::accumulate(std::begin(classNames), std::end(classNames), std::string(), [](std::string &ss, std::string &s) {return ss.empty() ? s : ss + "," + s; }) + ")";


		if (name != NULL) {
			errclass += "::";
			errclass += name;
		}

		errclass = "no overload for namespace or class " + errclass;
		return Nan::ThrowError(errclass.c_str());
	}

	
	std::vector<std::shared_ptr< o_r_function>> implementations;

	//copy all class functions by name from all descendant classes
	for (std::vector<std::string>::iterator cit = classNames.begin(); cit < classNames.end(); cit++) {
		if (_namespaces.count(ns) > 0 && _namespaces[ns].classes.count(*cit) > 0) {
			auto functions = _namespaces[ns].classes[*cit]->functions[name];

			implementations.insert(std::end(implementations), std::begin(functions), std::end(functions));
		}
	}


	for (auto i = 0; i < implementations.size(); i++) {
		auto check = implementations[i];
		assert((strcmp( check->functionName, name) == 0) && "function name must match");

		//check if the function parameter count equals the info parameters count, give a point in favor but only if reached maximum points
		auto rank = MatchOverload(&*check, info);
		if (rank > 0) {
			candidates.push_back(std::pair<int, o_r_function*>(rank, &*check));
		}

	}

	//log the best one
	//if none found, throw an exception that no overload satisfies the supplied parameters and the best overloaded candidate
	if (candidates.size() > 0) {
		auto bestOverload = std::max_element(candidates.begin(), candidates.end(), [](std::pair<int, o_r_function *> a, std::pair<int, o_r_function *> b) {return a.first < b.first; });
		return bestOverload->second->function(info);
	}

	return Nan::ThrowError("no overload fulfills the parameters passed");
}


Nan::NAN_METHOD_RETURN_TYPE overload_resolution::execute(const char * name_space, Nan::NAN_METHOD_ARGS_TYPE info){
	//assert(false);
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

	functionName = ((isStatic) ? "_" : "") + functionName;

	std::vector<std::string> prototypeClassChain;
	getPrototypeChain(info.This(), prototypeClassChain);
	if (prototypeClassChain.size() == 0) {
		//for functions without prototype chain, it means they are in the global namespace
		prototypeClassChain.push_back("");
	}

	return executeBestOverload(name_space, prototypeClassChain, functionName.c_str(), info);
}

bool overload_resolution::verifyObject(std::vector<std::shared_ptr<overload_info>> props, v8::Local<v8::Value> val) {
	auto mctx = Nan::GetCurrentContext();

	if (val->IsMap()) {
		
		auto omap = val.As<v8::Map>();
		for (std::vector<std::shared_ptr<overload_info>>::iterator pit = props.begin(); pit < props.end(); pit++) {
			auto oi = *pit;

			bool mapHasValue = false;

			//check the map has a key
			if (omap->Has(mctx, Nan::New<v8::String>(oi->parameterName).ToLocalChecked()).FromMaybe(mapHasValue) && !mapHasValue) {
				return false;
			}

			auto mval = omap->Get(mctx, Nan::New<v8::String>(oi->parameterName).ToLocalChecked());

			//check there is a value
			if (!Nan::New(oi->defaultValue)->IsUndefined() && mval.IsEmpty()) {
				return false;
			}
			if ((oi->type != determineType(mval.ToLocalChecked())) &&
				!isConvertibleTo(mval.ToLocalChecked(),oi->type)
				) {
				return false;
			}
		}
		return true;

	}
	else if (val->IsObject()) {
		auto obj = val.As<v8::Object>();
		for (std::vector<std::shared_ptr<overload_info>>::iterator pit = props.begin(); pit < props.end(); pit++) {
			auto oi = *pit;

			if (!obj->HasOwnProperty(Nan::New<v8::String>(oi->parameterName).ToLocalChecked())) {
				return false;
			}

			auto oval = obj->Get(mctx, Nan::New<v8::String>(oi->parameterName).ToLocalChecked());

			//check there is a value
			if (!Nan::New(oi->defaultValue)->IsUndefined() && oval.IsEmpty()) {
				return false;
			}
			if ((oi->type != determineType(oval.ToLocalChecked()))
				//&& !isConvertibleTo(oval.ToLocalChecked(), oi->type) //check convertible values?
				) {
				return false;
			}
		}
		return true;

	}

	return false;
}


MaybeLocal<v8::Value>  overload_resolution::GetFromObject(v8::Local<v8::Value> obj, const char * key) {
	auto mctx = Nan::GetCurrentContext();

	if (obj->IsMap()) {
		return obj.As<v8::Map>()->Get(mctx, Nan::New<v8::String>(key).ToLocalChecked());
	}
	else if (obj->IsObject()) {
		return obj.As<v8::Object>()->Get(mctx, Nan::New<v8::String>(key).ToLocalChecked());
	}
	else {
		return Nan::Undefined();
	}
}