#include "overload_resolution.h"

std::set<std::string> overload_resolution::_primitive_types = {"Number","String","Boolean"};

bool IStructuredObject::parse(v8::Local<v8::Value> obj) {
	return false;
}

v8::Local<v8::Value> IStructuredObject::ToObject() {
	return Nan::Null();
}

overload_info::overload_info(const char * parameterName, const char * type, v8::Local<v8::Value> defaultValue) {
	this->parameterName = parameterName;
	this->type = type;
	this->defaultValue.Reset(defaultValue);
}

overload_resolution::overload_resolution() {

}


void overload_resolution::register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const char * name) {
	assert(_types.count(name) == 0 && "type name already exists");

	auto ot = std::make_shared< object_type>();
	ot->function_template .Reset(functionTemplate);
	ot->name = name;
	_types[name] = ot;
}

void overload_resolution::addOverload(const char * ns, const char * name, std::vector<std::shared_ptr<overload_info>> arguments, Nan::FunctionCallback callback) {
	if (!_namespaces.count(ns)) {
		_namespaces[ns] = o_r_namespace();
		_namespaces[ns].name = ns;
	}
	
	if (!_namespaces[ns].functions.count(name)) {
		_namespaces[ns].functions[name] = std::vector<std::shared_ptr<o_r_function>>();
	}
	
	auto f = std::make_shared<o_r_function>();
	f->function = callback;
	f->functionName = name;
	f->parameters = arguments;
	_namespaces[ns].functions[name].push_back(f);
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
		if (structured[i].second.parse(param)) {
			return structured[i].first;
		}
	}

	//should not happen, unexpected object was passed!

	if (param->IsObject()) {
		return "Object";
	}

	//OR

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
	if (_primitive_types.count(type) && _primitive_types.count(determineType(param))) {
		return true;
	}

	//check prototypical inheritance
	if (_types.count(type)) {
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



	for (auto i = 0; i < parameterLength; i++) {
		int local_rank = 0;
		auto iparam = (info.Length() >= i) ? info[i] : Nan::Undefined();
		auto fparam = (func->parameters.size() > i) ? func->parameters.at(i) : nullptr;

		if (fparam == nullptr) {
			break;
		}
		
		//check if the function parameter and info parameter types are the same
		if (fparam->type == determineType(iparam)) {
			local_rank += 4;
		}
		

		//check if the function parameter and info parameter types are convertible
		if (isConvertibleTo(iparam, fparam->type)) {
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


void overload_resolution::executeBestOverload(const char * ns, const char * name, Nan::NAN_METHOD_ARGS_TYPE info) {
	std::vector<std::pair<int, o_r_function *>> candidates;

	auto implementations = _namespaces[ns].functions[name];

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

	return Nan::ThrowError("not overload fulfills the parameters passed");
}


Nan::NAN_METHOD_RETURN_TYPE overload_resolution::execute(const char * name_space, Nan::NAN_METHOD_ARGS_TYPE info){
	//assert(false);
	std::string functionName = *Nan::Utf8String(info.Callee()->GetName());
	std::string className = "";
	bool isStatic = false;

	std::string mangled = "";

	
	
	if (info.This()->IsFunction()) {
		//static
		className = *Nan::Utf8String(info.This().As<v8::Function>()->GetName());
		isStatic = true;
	}
	else {
		//member
		className = *Nan::Utf8String(info.This()->GetConstructorName());
	}

	//combine class + function + is_static to name
	if (className != "Object") {
		mangled = className + "::" + ((isStatic) ? "_" : "");
	}
	mangled  += functionName;

	return executeBestOverload(name_space, mangled.c_str(), info);
}