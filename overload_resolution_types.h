#ifndef _O_R_OVERLOAD_RESOLUTION_TYPES_H_
#define _O_R_OVERLOAD_RESOLUTION_TYPES_H_

#include <nan.h>
#include "FunctionCallbackInfo.h"

typedef const or ::FunctionCallbackInfo<v8::Value>& POLY_METHOD_ARGS_TYPE;
#define	POLY_METHOD(name)                                                       \
		Nan::NAN_METHOD_RETURN_TYPE name(POLY_METHOD_ARGS_TYPE info)

typedef void(*PolyFunctionCallback)(POLY_METHOD_ARGS_TYPE);


struct object_type {
	Nan::Persistent<v8::FunctionTemplate, Nan::CopyablePersistentTraits<v8::FunctionTemplate>> function_template;
	std::string ns;
	std::string name;
};



struct overload_info {
	std::string parameterName;
	std::string type;
	Nan::Persistent<v8::Value, Nan::CopyablePersistentTraits<v8::Value>> defaultValue;
	std::shared_ptr< or ::value_converter_base> value_converter;
	overload_info(const std::string parameterName, const std::string type);
	overload_info(const std::string parameterName, const std::string type, v8::Local<v8::Value> defaultValue);
	overload_info(const std::string parameterName, const std::string type, int defaultValue);
	overload_info(const std::string parameterName, const std::string type, double defaultValue);
	overload_info(const std::string parameterName, const std::string type, bool defaultValue);
	overload_info(const std::string parameterName, const std::string type, std::string defaultValue);
};

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type) {
	return std::make_shared<overload_info>(parameterName, type);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, v8::Local<v8::Value> defaultValue) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, bool defaultValue) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, int defaultValue) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, double defaultValue) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, std::string defaultValue) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type) {
	auto value_converter = std::make_shared < or ::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(parameterName, type);
	oi->value_converter = value_converter;

	return oi;
}

template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, std::shared_ptr<T> defaultValue) {
	auto value_converter = std::make_shared < or ::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(parameterName, type, value_converter->convert(defaultValue));
	oi->value_converter = value_converter;

	return oi;
}


struct o_r_function {
	PolyFunctionCallback function;
	std::string functionName;
	std::string className;
	bool is_constructor;
	bool is_static;
	std::vector<std::shared_ptr<overload_info>> parameters;
};

struct o_r_class {
	std::string className;
	std::map<std::string, std::vector<std::shared_ptr< o_r_function>>> functions;
};

struct o_r_namespace {
	std::string name;
	std::map<std::string, std::shared_ptr< o_r_class>> classes;
};

#endif