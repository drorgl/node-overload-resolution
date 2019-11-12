#ifndef _O_R_OVERLOAD_RESOLUTION_OVERLOAD_INFO_H_
#define _O_R_OVERLOAD_RESOLUTION_OVERLOAD_INFO_H_

#include <memory>
#include <string>
#include <nan.h>
#include "value_converter.h"
#include "value_converter_base.h"

struct overload_info {
	std::string parameterName;
	std::string type;
	Nan::Persistent<v8::Value, Nan::CopyablePersistentTraits<v8::Value>> defaultValue;
	std::shared_ptr<void> defaultSharedValue;
	std::shared_ptr< overres::value_converter_base> value_converter;
	overload_info(const std::string &&parameterName, const std::string &&type);
	overload_info(const std::string &&parameterName, const std::string &&type, v8::Local<v8::Value> defaultValue);
	overload_info(const std::string &&parameterName, const std::string &&type, const int defaultValue);
	overload_info(const std::string &&parameterName, const std::string &&type, const double defaultValue);
	overload_info(const std::string &&parameterName, const std::string &&type, const bool defaultValue);
	overload_info(const std::string &&parameterName, const std::string &&type, const std::string &&defaultValue);
};

inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName),std::move( type));
}

inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, v8::Local<v8::Value> defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName), std::move(type), defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type,const bool defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName),std::move( type), defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type,const int defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName), std::move(type), defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, const double defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName), std::move(type), defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, const std::string &&defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName), std::move(type), std::move(defaultValue));
}

template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type) {
	assert(!type.empty() && "type cannot be empty" );
	auto value_converter = std::make_shared < overres::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(std::move(parameterName), std::move(type));
	oi->value_converter = value_converter;

	return oi;
}

template<typename T, typename std::enable_if<!std::is_convertible<T, v8::Local<v8::Value>>::value>::type* = nullptr>
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, T defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	auto value_converter = std::make_shared < overres::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(std::move(parameterName),std::move( type), value_converter->convert(defaultValue));
	oi->value_converter = value_converter;

	return oi;
}

template<typename T, typename TREF = typename std::remove_reference<T>::type>
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, std::shared_ptr<TREF> defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	auto value_converter = std::make_shared < overres::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(std::move(parameterName),std::move( type), value_converter->convert(defaultValue));
	oi->value_converter = value_converter;
	
	oi->defaultSharedValue = defaultValue;

	return oi;
}

template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, v8::Local<v8::Value> defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	auto value_converter = std::make_shared < overres::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(std::move(parameterName), std::move(type), value_converter->convert(defaultValue));
	oi->value_converter = value_converter;

	return oi;
}

#endif