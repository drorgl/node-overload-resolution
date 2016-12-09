#ifndef _O_R_TESTER_VALUE_CONVERTER_H_
#define _O_R_TESTER_VALUE_CONVERTER_H_
#include "../overload_resolution.h"

#include "return_struct.h"

#include <map>


namespace or_value_converter {

	namespace general_callback {
		std::shared_ptr<overload_resolution> overload;
		NAN_METHOD(tester_callback) {
			return overload->execute("or_value_converter", info);
		}
	}

	POLY_METHOD(value_converter_number) {
		auto rt = std::make_shared<return_struct>();
		rt->type = "number";
		rt->value = std::to_string(info.at<int>(0));
		//printf("value %s", rt->value.c_str());
		info.SetReturnValue<std::shared_ptr<return_struct>>(rt);
		//info.SetReturnValue<return_struct>(rt);

		//info.GetReturnValue().Set(Nan::New(".number(" + std::to_string( info.at<int>(0)) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_string) {
		info.GetReturnValue().Set(Nan::New(".string(" + info.at<std::string>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_bool) {
		info.GetReturnValue().Set(Nan::New(".bool(" + std::to_string(info.at<bool>(0)) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_date) {
		info.GetReturnValue().Set(Nan::New(".date(" + std::to_string(info.at<double>(0)) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_function) {
		//info.GetReturnValue().Set(Nan::New(".function(" + info.at<Nan::Callback>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_buffer) {
		//info.GetReturnValue().Set(Nan::New(".buffer(" + info.at<std::vector<int8_t>>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_map) {
		//info.GetReturnValue().Set(Nan::New(".map(" + info.at<std::map<std::string,int>>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_set) {
		//info.GetReturnValue().Set(Nan::New(".set(" + info.at<std::set<int>>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_promise) {
		//info.GetReturnValue().Set(Nan::New(".promise(" + info.at<>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_proxy) {
		//info.GetReturnValue().Set(Nan::New(".proxy(" + info.at<>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_regexp) {
		info.GetReturnValue().Set(Nan::New(".regexp(" + info.at<std::string>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_base_class) {
		//info.GetReturnValue().Set(Nan::New(".base_class(" + info.at<base_class>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_derived_class) {
		//info.GetReturnValue().Set(Nan::New(".derived_class(" + info.at<derived_class>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_struct_A) {
		//info.GetReturnValue().Set(Nan::New(".struct_A(" + info.at<struct_A>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_struct_B) {
		//info.GetReturnValue().Set(Nan::New(".struct_B(" + info.at<struct_B>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_array) {
		//info.GetReturnValue().Set(Nan::New(".array(" + info.at<std::vector<int>>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter) {
		info.GetReturnValue().Set(Nan::New(".no_parameters()").ToLocalChecked());
	}

	void RegisterORTesters(v8::Handle<v8::Object> target, std::shared_ptr<overload_resolution> overload) {
		auto loverload = overload;
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<int>("a","int") }, value_converter_number);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::string>("a","string") }, value_converter_string);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<bool>("a","Boolean") }, value_converter_bool);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<double>("a","Date") }, value_converter_date);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<or::Callback>>("a","Function") }, value_converter_function);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<std::vector<uint8_t>>>("a","Buffer") }, value_converter_buffer);
		//overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<std::map<std::string,int>>>("a","Map") }, value_converter_map);
		//overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::set<std::string>>("a","Set") }, value_converter_set);
		//overload->addOverload("or_value_converter", "", "value_converter", { make_param<>("a","Promise") }, value_converter_promise);
		//overload->addOverload("or_value_converter", "", "value_converter", { make_param<>("a","Proxy") }, value_converter_proxy);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::string>("a","RegExp") }, value_converter_regexp);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<base_class*>("a","base_class") }, value_converter_base_class);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<derived_class*>("a","derived_class") }, value_converter_derived_class);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<struct_A>>("a","struct_A") }, value_converter_struct_A);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<struct_B>>("a","struct_B") }, value_converter_struct_B);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<std::vector<int>>>("a","Array") }, value_converter_array);
		overload->addOverload("or_value_converter", "", "value_converter", {}, value_converter);

		general_callback::overload = overload;
		Nan::SetMethod(target, "value_converter", general_callback::tester_callback);
	}

}

#endif