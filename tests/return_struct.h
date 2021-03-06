#ifndef _TESTER_RETURN_STRUCT_H_
#define _TESTER_RETURN_STRUCT_H_

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_version.h>
#include <node_buffer.h>
#include <string.h>
//#include <nan.h>


#include <memory>
#include <string>
//#include "../IStructuredObject.h"

#include <exception>

#include "../type_system.h"

/** 
 * @addtogroup tests
 * @{
 */

/**
 * @brief example struct for returning structs
 * 
 * @tparam T 
 */
template <typename T>
class return_struct : public IStructuredObject {
private:
	std::string _v8_value_type;
	std::vector<std::shared_ptr<overload_info>> _definition;

public:
	return_struct() {
		throw std::runtime_error("invalid use for return_struct");
	}

	return_struct(std::string v8_value_type) {
		_v8_value_type = v8_value_type;
		_definition = {
			make_param("type","String") ,
			make_param("value",std::move(v8_value_type))
		};
	}

	std::string type;
	T value;

	virtual bool verify(overres::type_system * ovres, v8::Local<v8::Value> obj) {
		return ovres->verifyObject(return_struct::_definition, obj);
	}
	virtual bool parse(v8::Local<v8::Value> obj) {
		this->type = *Nan::Utf8String(overres::type_system::GetFromObject(obj, "type").ToLocalChecked());

		auto vconverter = std::make_shared< overres::value_converter<T>>();
		this->value = vconverter->convert(overres::type_system::GetFromObject(obj, "value").ToLocalChecked());
		//this->value = *Nan::Utf8String(ovres->GetFromObject(obj, "value").ToLocalChecked());

		return true;
	}

	virtual v8::Local<v8::Value> ToObject() {
		auto retval = Nan::New<v8::Object>();
		Nan::Set(retval,Nan::New<v8::String>("type").ToLocalChecked(), Nan::New<v8::String>(this->type).ToLocalChecked());

		auto vconverter = std::make_shared< overres::value_converter<T>>();
		Nan::Set(retval,Nan::New<v8::String>("value").ToLocalChecked(), vconverter->convert( this->value ));
		//retval->Set(Nan::New<v8::String>("value").ToLocalChecked(), Nan::New<v8::String>(this->value).ToLocalChecked());
		return retval;
	}

};

/** @}*/
#endif