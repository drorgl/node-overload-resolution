#include "type_system.h"
#include <tracer.h>
#include "overload_info.h"
#include <cmath>

namespace overres {
	static void Log(LogLevel level, std::string &&message) {
		if (tracer::log_level <= level) {
			tracer::Log("type_system", level, std::move(message));
		}
	}

	static void Log(LogLevel level, std::function<std::string()> message) {
		if (tracer::log_level <= level) {
			tracer::Log("type_system", level, message);
		}
	}



	std::unordered_set<std::string> type_system::convertible_primitive_types = { "Number","String","Boolean" };

	std::unordered_set<std::string> type_system::primitive_types = { "Number","String","Boolean","Date","Buffer","Function","Map","Set","Null","Promise","Proxy","RegExp","Array" };

	type_system::type_system() {
		_structured_factory = std::make_shared<Factory<IStructuredObject>>();
	}

	void type_system::reset() {
		_structured_factory = nullptr;
		_types.clear();
		_type_aliases.clear();
		_namespaces.clear();
	}

	type_system::~type_system() {
		reset();
	}

	void type_system::add_type_alias(std::string alias, std::string type) {
		assert(!alias.empty() && "alias can not be empty");
		assert(!type.empty() && "alias type can not be empty");
		Log(LogLevel::DEBUG, [&alias, &type]() {return "adding alias " + alias + " for " + type; });
		//_type_system.add_type_alias(alias, type);
		_type_aliases[alias] = type;
	}

	std::string type_system::drill_type_aliases(const std::string& alias) {
		auto type_alias = _type_aliases.find(alias);
		if (type_alias != _type_aliases.end()) {
			auto type = type_alias->second;
			Log(LogLevel::TRACE, [&alias, &type]() {return "drilling alias " + alias + " of " + type; });
			return drill_type_aliases(type);
		}
		else {
			return alias;
		}

	}



	std::string type_system::normalize_types(std::string type) {
		//if type was already normalized, return the cached normalization
		auto cached = _cached_normalization.find(type);
		if (cached != _cached_normalization.end()) {
			return cached->second;
		}

		Log(LogLevel::TRACE, [&type]() {return "normalizing type " + type; });

		auto raw_type = type;
		auto genericBegin = type.find("<");
		if (genericBegin == std::string::npos) {
			auto drilled_types = drill_type_aliases(type);
			_cached_normalization[raw_type] = drilled_types;
			return drilled_types;
		}

		auto genericEnd = type.find_last_of(">");

		assert(genericEnd != std::string::npos && "generic types should be between <>");
		if (genericEnd == std::string::npos) {
			Log(LogLevel::WARN, [&type]() {return "normalize type " + type + " generic types should be between <>"; });
		}

		auto genericType = type.substr(0, genericBegin);
		//types.insert(genericType);
		type = type.replace(0, genericBegin, normalize_types(genericType));
		auto between = type.substr(genericBegin + 1, genericEnd - genericBegin - 1);
		type = type.replace(genericBegin + 1, genericEnd - genericBegin - 1, normalize_types(between));

		_cached_normalization[raw_type] = type;
		return type;
	}





	void type_system::split_generic_types(std::string type, std::vector<std::string> &types) {
		Log(LogLevel::TRACE, [&type, types]() {return "splitting generic types " + type; });
		auto genericBegin = type.find("<");
		if (genericBegin == std::string::npos) {
			types.push_back(drill_type_aliases(type));
			return;
		}

		auto genericEnd = type.find_last_of(">");

		assert(genericEnd != std::string::npos && "generic types should be between <>");
		if (genericEnd == std::string::npos) {
			Log(LogLevel::WARN, [&type]() {return "split generic type " + type + " generic types should be between <>"; });
		}

		auto genericType = type.substr(0, genericBegin);
		types.push_back(genericType);
		auto between = type.substr(genericBegin + 1, genericEnd - genericBegin - 1);
		split_generic_types(between, types);
	}


	//TODO: possibly improve the performance by limiting the number of array object read
	void type_system::get_array_types(v8::Local<v8::Value> arr, std::set<std::string> &types) {
		auto v8arr = arr.As<v8::Array>();

		//speed optimization, could create problems for large inconsistent arrays
		if (v8arr->Length() <= 10) {
			for (uint32_t i = 0; i < v8arr->Length(); i++) {
				types.insert(drill_type_aliases(determineType(v8arr->Get(i))));
			}
		}
		else {
			for (uint32_t i = 0; i < v8arr->Length(); i += (v8arr->Length() / 10)) {
				types.insert(drill_type_aliases(determineType(v8arr->Get(i))));
			}
		}
		//TODO: add arr?... could be problematic
		Log(LogLevel::TRACE, [&arr, &types]() {return "get array types " + tracer::join(types, ", "); });
	}

	std::string type_system::determineType(v8::Local<v8::Value> param) {
		//TODO: serialize param
		Log(LogLevel::TRACE, [&param]() {return "determine type " + std::string(overres::Utf8String(param->ToDetailString())); });
		if (param->IsArray()) {
			std::set <std::string> arrtypes;
			get_array_types(param, arrtypes);

			//if type is determined, that means that only one type was in the array
			//no values (no type) or more than one type in the array would not return a type
			if (arrtypes.size() == 1) {
				std::string s;
				s = "Array<";
				s += *arrtypes.begin();
				s += ">";
				return s;
			}
			else {
				return "Array";
			}

		}

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
		if (param->IsArrayBuffer() || param->IsArrayBufferView() || param->IsTypedArray() || node::Buffer::HasInstance(param)) {
#else
		if (node::Buffer::HasInstance(param)) {
#endif
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

#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		if (param->IsGeneratorFunction()) {
			return "ConstructorFunction";
		}

		if (param->IsMap()) {
			return "Map";
		}

		if (param->IsSet()) {
			return "Set";
		}
#endif

		if (param->IsNull() || param->IsUndefined()) {
			return "Null";
		}

		if (param->IsNumber()) {
			return "Number";
		}

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
		if (param->IsPromise()) {
			return "Promise";
		}
#endif

#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		if (param->IsProxy()) {
			return "Proxy";
		}
#endif

		if (param->IsRegExp()) {
			return "RegExp";
		}

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
		if (param->IsSymbol()) {
			return "String";
		}
#endif

		if (param->IsString()) {
			return "String";
		}

		//first, check the list of registrations, if one of the types match, they are a higher priority

		std::map<std::string, std::shared_ptr<object_type>>::iterator it;

		std::vector<std::shared_ptr<object_type>> alternatives;

		//might be able to optimize with FindInstanceInPrototypeChain
		auto param_name = overres::Utf8String(param.As<v8::Object>()->GetConstructorName());

		std::vector<std::string> chain;
		getPrototypeChain(param, chain);
		for (auto &&chain_link : chain) {
			auto registered_type = _types[chain_link];
			if (Nan::New<v8::FunctionTemplate>(registered_type->function_template)->HasInstance(param)) {
				if (strcmp(param_name.c_str(), registered_type->name.c_str()) == 0) {
					return drill_type_aliases(registered_type->name);
				}
				else {
					alternatives.push_back(registered_type);
				}
			}
		}

		if (alternatives.size() > 0) {
			assert(false && "object base was found but not object itself!");
			//TODO: add which object was found
			Log(LogLevel::ERROR, []() {return "object base was found but not object itself!"; });
		}

		//possible performance optimization by caching the all() values
		auto structured = _structured_factory->all();
		for (size_t i = 0; i < structured.size(); i++) {
			if (structured[i].second->verify(this, param)) {
				return drill_type_aliases(structured[i].first);
			}
		}

		//should not happen, unexpected object was passed!
		if (param->IsObject()) {
			return "Object";
		}

		return "Unknown";
	}

	bool type_system::isArrayConvertibleTo(v8::Local<v8::Value> param, std::string &param_type, const std::string type) {
		Log(LogLevel::TRACE, [&param_type, &type]() {return "is array convertible " + param_type + " > " + type; });


		std::vector<std::string> generic_param_types;
		std::vector<std::string> generic_types;

		split_generic_types(param_type, generic_param_types);
		split_generic_types(type, generic_types);


		auto generic_array_types_length = (std::max)(generic_param_types.size(), generic_types.size());
		if (generic_array_types_length > 0) {
			if (normalize_types(generic_param_types[0]) != "Array"){
				return false;
			}
			if (normalize_types(generic_types[0]) != "Array") {
				return false;
			}
		}

		for (size_t i = 0; i < generic_array_types_length; i++) {
			if (generic_param_types.size() > i && generic_types.size() > i) {
				auto normalized_param = normalize_types(generic_param_types[i]);
				auto normalized_type = normalize_types(generic_types[i]);

				if ((normalized_param == "Array" && normalized_type != "Array") || 
					(normalized_param != "Array" && normalized_type == "Array")) {
					return false;
				} else if (normalized_param != normalized_type) {
					if (!isConvertibleTo(param, normalized_param, normalized_type)) {
						return false;
					}
				}
			}
		}
		return true;
	}

	bool type_system::isConvertibleTo(v8::Local<v8::Value> param, std::string &param_type, const std::string type) {
		Log(LogLevel::TRACE, [&param, &type]() {return "checking if object " + std::string(overres::Utf8String(param->ToDetailString())) + " is convertible to " + type; });
		//if converting to number, check that the numbervalue is not nan
		if (type == "Number") {
			if (std::isnan(param->NumberValue())) {
				return false;
			}
			else {
				return true;
			}
		}

		//if converting to primitive from a primitive, it is possible
		//TODO: not always, a string can be converted to number only if it contains a number
		if (convertible_primitive_types.count(type) > 0 && convertible_primitive_types.count(param_type) > 0) {
			return true;
		}

		//check prototypical inheritance
		auto registered_type = _types.find(type);
		if (registered_type != _types.end()) {
			if (Nan::New<v8::FunctionTemplate>(registered_type->second->function_template)->HasInstance(param)) {
				return true;
			}
		}

		//if converting from anything to boolean, it is possible
		if (type == "Boolean") {
			return true;
		}

		//functions can always be assigned a null, we just ignore the callback
		if (type == "Function" && (param_type == "Null" || param_type == "Undefined")) {
			return true;
		}

		return false;
	}


	void type_system::getPrototypeChain(v8::Local<v8::Value> param, std::vector<std::string> &chain) {
		if (!param->IsObject()) {
			return;
		}

		auto pobject = param.As<v8::Object>();

		std::string constructorName = overres::Utf8String(pobject->GetConstructorName());
		if (constructorName == "Object") {
			return;
		}

		chain.push_back(constructorName);
		getPrototypeChain(pobject->GetPrototype(), chain);
		Log(LogLevel::TRACE, [&param, &chain]() {return "checking prototype chain for " + std::string(overres::Utf8String(param->ToDetailString())) + ": " + tracer::join(chain, ", "); });
	}


	bool type_system::verifyObject(std::vector<std::shared_ptr<overload_info>> props, v8::Local<v8::Value> val) {
		//TODO: add default values
		Log(LogLevel::TRACE, [&props, &val]() {return "verifying object " + tracer::join(props, [](const std::shared_ptr<overload_info> oi) {return oi->type + " " + oi->parameterName; }, ", ") + std::string(overres::Utf8String(val->ToDetailString())); });

		auto mctx = Nan::GetCurrentContext();
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		if (val->IsMap()) {

			auto omap = val.As<v8::Map>();
			for (auto &&pit : props) {
				auto oi = pit;

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
				auto mval_type = determineType(mval.ToLocalChecked());
				if ((oi->type != mval_type) &&
					!isConvertibleTo(mval.ToLocalChecked(),mval_type, oi->type)
					) {
					return false;
				}
			}
			return true;

		}
		else 
#endif
			if (val->IsObject()) {
			auto obj = val.As<v8::Object>();
			for (auto &&pit : props) {
				auto oi = pit;

				if (!obj->HasOwnProperty(Nan::New<v8::String>(oi->parameterName).ToLocalChecked())) {
					return false;
				}

				auto oval = Nan::Get(obj, Nan::New<v8::String>(oi->parameterName).ToLocalChecked());

				//check there is a value
				if (!oi->defaultValue.IsEmpty() && !Nan::New(oi->defaultValue)->IsUndefined() && oval.IsEmpty()) {
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


	Nan::MaybeLocal<v8::Value>  type_system::GetFromObject(v8::Local<v8::Value> obj, const std::string key) {
		auto mctx = Nan::GetCurrentContext();
		
		Nan::MaybeLocal<v8::Value> ret;

#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		if (obj->IsMap()) {
			ret = Nan::Get(obj.As<v8::Map>(), Nan::New<v8::String>(key).ToLocalChecked());// obj.As<v8::Map>()->Get(mctx, Nan::New<v8::String>(key).ToLocalChecked());
		}
		else 
#endif
			if (obj->IsObject()) {
			ret = Nan::Get(obj.As<v8::Object>(), Nan::New<v8::String>(key).ToLocalChecked());// obj.As<v8::Object>()->Get(mctx, Nan::New<v8::String>(key).ToLocalChecked());
		}
		else {
			ret = Nan::Undefined();
		}

		Log(LogLevel::TRACE, [&obj, &key, &ret]() {return "retrieving " + key + " = " + ((!ret.IsEmpty()) ? std::string(overres::Utf8String(ret.ToLocalChecked()->ToDetailString())) : "unknown") + " from " + std::string(overres::Utf8String(obj->ToDetailString())); });

		return ret;
	}

	std::shared_ptr<object_type> type_system::get_type(std::string &type) {
		auto res = _types.find(type);
		if (res == std::end(_types)) {
			return nullptr;
		}
		return res->second;
	}

	void type_system::add_overload(const std::string &ns, const std::string &className, const std::string &functionName, std::shared_ptr<o_r_function> func) {
		_namespaces[ns]->classes[className]->functions[functionName].push_back(func);
	}

	bool type_system::validate_type_registrations() {
		bool valid = true;
		for (auto ns = std::begin(_namespaces); ns != std::end(_namespaces); ns++) {
			//for each namespace
			for (auto cls = std::begin(ns->second->classes); cls != std::end(ns->second->classes); cls++) {
				//for each class 
				for (auto fn = std::begin(cls->second->functions); fn != std::end(cls->second->functions); fn++) {
					//for each function
					for (std::vector<std::shared_ptr< o_r_function>>::iterator fnoverload = std::begin(fn->second); fnoverload != std::end(fn->second); fnoverload++) {
						//for each function overload
						//TODO: add duplicate parameters testing
						for (std::vector<std::shared_ptr<overload_info>>::iterator olinfo = std::begin(fnoverload->get()->parameters); olinfo != std::end(fnoverload->get()->parameters); olinfo++) {
							//for each overload parameter
							auto type = drill_type_aliases(olinfo->get()->type);

							if ((_types.count(type) == 0) &&
								(!_structured_factory->has_type(type)) &&
								(primitive_types.count(type) == 0))
							{
								//if normal type checking failed, do a generic type checking
								std::vector<std::string> types;
								split_generic_types(type, types);

								for (auto &&separate_type : types){// = std::begin(types); separate_type != std::end(types); separate_type++) {
									if ((_types.count(separate_type) == 0) &&
										(!_structured_factory->has_type(separate_type.c_str())) &&
										(primitive_types.count(separate_type) == 0) && (separate_type != "Object")) {
										printf("cannot find type %s in %s::%s::%s\r\n", separate_type.c_str(), ns->second->name.c_str(), cls->second->className.c_str(), (*fnoverload)->functionName.c_str());
										Log(LogLevel::ERROR, [&separate_type, &ns, &cls, &fnoverload]() {return "cannot find type " + separate_type + " in " + ns->second->name + "::" + cls->second->className + "::" + (*fnoverload)->functionName; });
										valid = false;
									}
								}
							}
						}
					}
				}
			}
		}
		return valid;
	}


	void type_system::create_function_store(const std::string &ns, const std::string &className, const std::string &functionName) {
		Log(LogLevel::TRACE, [&ns, &className, &functionName]() {return "create function store " + ns + "::" + className + "::" + functionName; });
		//check if namespace exists, if not, create
		if (!_namespaces.count(ns)) {
			_namespaces[ns] = std::make_shared<o_r_namespace>();
			_namespaces[ns]->name = ns;
		}

		//check if class exists, if not, create
		if (!_namespaces[ns]->classes.count(className)) {
			_namespaces[ns]->classes[className] = std::make_shared<o_r_class>();
			_namespaces[ns]->classes[className]->className = className;
		}

		//check functions collection exists, if not, create
		if (!_namespaces[ns]->classes[className]->functions.count(functionName)) {
			_namespaces[ns]->classes[className]->functions[functionName] = std::vector<std::shared_ptr<o_r_function>>();
		}
	}

	void type_system::get_classes(const std::string &ns,const std::vector<std::string> &classNames, std::vector < std::shared_ptr< o_r_class>> &classes) {
		for (auto &&cit : classNames) {
			if (_namespaces.count(ns) > 0 && _namespaces[ns]->classes.count(cit) > 0) {
				classes.push_back(_namespaces[ns]->classes[cit]);
			}
		}
	}

	void type_system::get_functions(const std::string &ns, const std::vector<std::string> &classNames, const std::string &functionName, std::vector<std::shared_ptr< o_r_function>> &implementations) {
		for (auto &&cit : classNames) {
			if (_namespaces.count(ns) > 0 && _namespaces[ns]->classes.count(cit) > 0) {
				auto functions = _namespaces[ns]->classes[cit]->functions[functionName];

				implementations.insert(std::end(implementations), std::begin(functions), std::end(functions));
			}
		}
	}

	void type_system::LogDebug(std::function<std::string()> message) {
		Log(LogLevel::DEBUG, message);
	}
	void type_system::LogWarn(std::function<std::string()> message) {
		Log(LogLevel::WARN, message);
	}

};