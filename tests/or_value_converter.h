#ifndef _O_R_TESTER_VALUE_CONVERTER_H_
#define _O_R_TESTER_VALUE_CONVERTER_H_
#include "../overload_resolution.h"

#include "return_struct.h"

#include <map>

#include "threaded_tester.h"


namespace overres_value_converter {
	ThreadedTester _threaded_tester;


	namespace general_callback {
		std::shared_ptr<overload_resolution> overload;
		NAN_METHOD(tester_callback) {
			return overload->execute("or_value_converter", info);
		}
	}

	POLY_METHOD(value_converter_number) {
		auto rt = std::make_shared<return_struct<int>>("Number");
		rt->type = "number";
		rt->value = info.at<int>(0);
		info.SetReturnValue<std::shared_ptr<return_struct<int>>>(rt);
	}

	POLY_METHOD(value_converter_string) {
		auto rt = std::make_shared<return_struct<std::string>>("String");
		rt->type = "string";
		rt->value = info.at<std::string>(0);
		info.SetReturnValue<std::shared_ptr<return_struct<std::string>>>(rt);
	}

	POLY_METHOD(value_converter_bool) {
		auto rt = std::make_shared<return_struct<bool>>("Bool");
		rt->type = "bool";
		rt->value = info.at<bool>(0);
		info.SetReturnValue<std::shared_ptr<return_struct<bool>>>(rt);
	}

	POLY_METHOD(value_converter_date) {
		auto rt = std::make_shared<return_struct<overres::DateTime>>("Date");
		rt->type = "date";
		rt->value = info.at<overres::DateTime>(0);
		info.SetReturnValue<std::shared_ptr<return_struct<overres::DateTime>>>(rt);
	}

	POLY_METHOD(value_converter_function) {
		auto rt = std::make_shared<return_struct<std::shared_ptr<overres::Callback>>>("Function");
		rt->type = "function";
		rt->value = info.at<std::shared_ptr< overres::Callback>>(0);
		rt->value->Call({ overres::make_value<std::string>("callback called")});
		info.SetReturnValue<std::shared_ptr<return_struct<std::shared_ptr< overres::Callback>>>>(rt);
	}

	POLY_METHOD(value_converter_buffer) {
		auto rt = std::make_shared<return_struct<std::shared_ptr<std::vector<uint8_t>>>>("Buffer");
		rt->type = "buffer";
		rt->value = info.at<std::shared_ptr<std::vector<uint8_t>>>(0);
		
		info.SetReturnValue<std::shared_ptr<return_struct<std::shared_ptr<std::vector<uint8_t>>>>>(rt);

		//info.GetReturnValue().Set(Nan::New(".buffer(" + info.at<std::vector<int8_t>>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_map) {
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		auto rt = std::make_shared<return_struct<std::shared_ptr<std::map<std::string,int>>>>("Map");
		rt->type = "map";
		rt->value = info.at<std::shared_ptr<std::map<std::string, int>>>(0);

		info.SetReturnValue<std::shared_ptr<return_struct<std::shared_ptr<std::map<std::string,int>>>>>(rt);


		//info.GetReturnValue().Set(Nan::New(".map(" + info.at<std::map<std::string,int>>(0) + ")").ToLocalChecked());
#endif
	}

	POLY_METHOD(value_converter_set) {
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION		
		auto rt = std::make_shared<return_struct<std::shared_ptr<std::set<std::string>>>>("Set");
		rt->type = "set";
		rt->value = info.at<std::shared_ptr<std::set<std::string>>>(0);

		info.SetReturnValue<std::shared_ptr<return_struct<std::shared_ptr<std::set<std::string>>>>>(rt);


		//info.GetReturnValue().Set(Nan::New(".set(" + info.at<std::set<int>>(0) + ")").ToLocalChecked());
#endif
	}

	POLY_METHOD(value_converter_promise) {
		//info.GetReturnValue().Set(Nan::New(".promise(" + info.at<>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_proxy) {
		//info.GetReturnValue().Set(Nan::New(".proxy(" + info.at<>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_regexp) {
		auto rt = std::make_shared<return_struct<std::string>>("string");
		rt->type = "string";
		rt->value = info.at<std::string>(0);

		info.SetReturnValue<std::shared_ptr<return_struct<std::string>>>(rt);


		//info.GetReturnValue().Set(Nan::New(".regexp(" + info.at<std::string>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_base_class) {

		auto rt = std::make_shared<return_struct<base_class*>>("base_class");
		rt->type = "base_class";
		rt->value = info.at<base_class*>(0);

		info.SetReturnValue<std::shared_ptr<return_struct<base_class*>>>(rt);


		//info.GetReturnValue().Set(Nan::New(".base_class(" + info.at<base_class>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_derived_class) {
		auto rt = std::make_shared<return_struct<derived_class*>>("derived_class");
		rt->type = "derived_class";
		rt->value = info.at<derived_class*>(0);

		info.SetReturnValue<std::shared_ptr<return_struct<derived_class*>>>(rt);

		//info.GetReturnValue().Set(Nan::New(".derived_class(" + info.at<derived_class>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_struct_A) {
		auto rt = std::make_shared<return_struct<std::shared_ptr<struct_A>>>("struct_A");
		rt->type = "struct_A";
		rt->value = info.at<std::shared_ptr<struct_A>>(0);

		info.SetReturnValue<std::shared_ptr<return_struct<std::shared_ptr<struct_A>>>>(rt);

		//info.GetReturnValue().Set(Nan::New(".struct_A(" + info.at<struct_A>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_struct_B) {
		auto rt = std::make_shared<return_struct<std::shared_ptr<struct_B>>>("struct_B");
		rt->type = "struct_B";
		rt->value = info.at<std::shared_ptr<struct_B>>(0);

		info.SetReturnValue<std::shared_ptr<return_struct<std::shared_ptr<struct_B>>>>(rt);

		//info.GetReturnValue().Set(Nan::New(".struct_B(" + info.at<struct_B>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter_array) {
		auto rt = std::make_shared<return_struct<std::shared_ptr<std::vector<int>>>>("array");
		rt->type = "array";
		rt->value = info.at<std::shared_ptr<std::vector<int>>>(0);

		info.SetReturnValue<std::shared_ptr<return_struct<std::shared_ptr<std::vector<int>>>>>(rt);


		//info.GetReturnValue().Set(Nan::New(".array(" + info.at<std::vector<int>>(0) + ")").ToLocalChecked());
	}

	POLY_METHOD(value_converter) {
		info.GetReturnValue().Set(Nan::New(".no_parameters").ToLocalChecked());
	}

	POLY_METHOD(value_converter_async_callback) {
		auto times = info.at<int>(0);
		auto cb = info.at<std::shared_ptr< overres::AsyncCallback>>(1);
		cb->set_ref(true);
		_threaded_tester.Enqueue(times, [=]() {
			auto callback = cb;
			callback->Call({ overres::make_value(0)});
		});
		_threaded_tester.Start();
		info.SetReturnValue("hello"s);
	}

	void RegisterORTesters(v8::Handle<v8::Object> target, std::shared_ptr<overload_resolution> overload) {
		auto loverload = overload;
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<int>("a","int") }, value_converter_number);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::string>("a","string") }, value_converter_string);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<bool>("a","Boolean") }, value_converter_bool);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<overres::DateTime>("a","Date") }, value_converter_date);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<overres::Callback>>("a","Function") }, value_converter_function);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<std::vector<uint8_t>>>("a","Buffer") }, value_converter_buffer);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<std::map<std::string,int>>>("a","Map") }, value_converter_map);
		//overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<std::map<int,int>>>("a","Map") }, value_converter_map);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<std::set<std::string>>>("a","Set") }, value_converter_set);
#endif
		//overload->addOverload("or_value_converter", "", "value_converter", { make_param<>("a","Promise") }, value_converter_promise);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		//overload->addOverload("or_value_converter", "", "value_converter", { make_param<>("a","Proxy") }, value_converter_proxy);
#endif
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::string>("a","RegExp") }, value_converter_regexp);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<base_class*>("a","base_class") }, value_converter_base_class);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<derived_class*>("a","derived_class") }, value_converter_derived_class);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<struct_A>>("a","struct_A") }, value_converter_struct_A);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<struct_B>>("a","struct_B") }, value_converter_struct_B);
		overload->addOverload("or_value_converter", "", "value_converter", { make_param<std::shared_ptr<std::vector<int>>>("a","Array") }, value_converter_array);
		overload->addOverload("or_value_converter", "", "value_converter", {}, value_converter);


		overload->addOverload("or_value_converter", "", "async_callback", {
			make_param<int>("times","int"), 
			make_param < std::shared_ptr< overres::AsyncCallback>>("cb","Function")
		}, value_converter_async_callback);

		general_callback::overload = overload;
		Nan::SetMethod(target, "value_converter", general_callback::tester_callback);
		Nan::SetMethod(target, "async_callback", general_callback::tester_callback);
	}

}

#endif