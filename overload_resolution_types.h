#ifndef _O_R_OVERLOAD_RESOLUTION_TYPES_H_
#define _O_R_OVERLOAD_RESOLUTION_TYPES_H_

#include <nan.h>
#include <unordered_map>
#include "FunctionCallbackInfo.h"

typedef const or ::FunctionCallbackInfo<v8::Value>& POLY_METHOD_ARGS_TYPE;
#define	POLY_METHOD(name)                                                       \
		Nan::NAN_METHOD_RETURN_TYPE name(POLY_METHOD_ARGS_TYPE info)

typedef void(*PolyFunctionCallback)(POLY_METHOD_ARGS_TYPE);


struct object_type {
	Nan::Persistent<v8::FunctionTemplate, Nan::CopyablePersistentTraits<v8::FunctionTemplate>> function_template;
	std::string ns;
	std::string name;
	std::shared_ptr< or ::value_converter_base> value_converter;
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
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(parameterName, type);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, v8::Local<v8::Value> defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, bool defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, int defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, double defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, std::string defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type) {
	assert(!type.empty() && "type cannot be empty" );
	auto value_converter = std::make_shared < or ::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(parameterName, type);
	oi->value_converter = value_converter;

	return oi;
}

template<typename T, typename std::enable_if<!std::is_convertible<T, v8::Local<v8::Value>>::value>::type* = nullptr>
inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, T defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	auto value_converter = std::make_shared < or ::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(parameterName, type, value_converter->convert(defaultValue));
	oi->value_converter = value_converter;

	return oi;
}

template<typename T, typename TREF = std::remove_reference<T>::type>
inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, std::shared_ptr<TREF> defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	auto value_converter = std::make_shared < or ::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(parameterName, type, value_converter->convert(defaultValue));
	oi->value_converter = value_converter;
	
	//a workaround for locker for defaultValue, should be stored in overload_info and released on removal
	auto lockptr = new std::shared_ptr<TREF>(defaultValue);

	return oi;
}

template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, v8::Local<v8::Value> defaultValue) {
	assert(!type.empty() && "type cannot be empty");
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
	std::unordered_map<std::string, std::vector<std::shared_ptr< o_r_function>>> functions;
};

struct o_r_namespace {
	std::string name;
	std::unordered_map<std::string, std::shared_ptr< o_r_class>> classes;
};

#endif