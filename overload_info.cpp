#include "overload_info.h"

#include <nan.h>
#include <string>


overload_info::overload_info(const std::string parameterName, const std::string type) {
	this->parameterName = parameterName;
	this->type = type;
}

overload_info::overload_info(const std::string parameterName, const std::string type, v8::Local<v8::Value> defaultValue) {
	this->parameterName = parameterName;
	this->type = type;
	this->defaultValue.Reset(defaultValue);
}

overload_info::overload_info(const std::string parameterName, const std::string type, int defaultValue) : overload_info(parameterName, type, Nan::New(defaultValue)) {}
overload_info::overload_info(const std::string parameterName, const std::string type, bool defaultValue) : overload_info(parameterName, type, Nan::New(defaultValue)) {}
overload_info::overload_info(const std::string parameterName, const std::string type, std::string defaultValue) : overload_info(parameterName, type, Nan::New(defaultValue).ToLocalChecked()) {}
overload_info::overload_info(const std::string parameterName, const std::string type, double defaultValue) : overload_info(parameterName, type, Nan::New(defaultValue)) {}
