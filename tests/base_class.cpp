#include "base_class.h"

namespace base_class_general_callback {
	std::shared_ptr<overload_resolution> overload;
	NAN_METHOD(overload_callback) {
		return overload->execute("", info);
	}
}

	Nan::Persistent<FunctionTemplate> base_class::constructor;

	void base_class::Init(Handle<Object> target, std::shared_ptr<overload_resolution> overload) {
		Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(base_class::New);
		constructor.Reset(ctor);
		ctor->InstanceTemplate()->SetInternalFieldCount(1);
		ctor->SetClassName(Nan::New("base_class").ToLocalChecked());

		//Nan::SetPrototypeMethod(ctor, "base_function", base_function);

		overload->addOverload("", "base_class","base_function", {}, base_function);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, base_function_number);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","String",Nan::Undefined()) }, base_function_string);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, base_function_bool);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, base_function_date);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, base_function_function);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, base_function_buffer);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, base_function_map);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, base_function_set);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, base_function_promise);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, base_function_proxy);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, base_function_regexp);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, base_function_base_class);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, base_function_derived_class);
		overload->addOverload("", "base_class","base_function", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) },      base_function_struct_A);
		overload->addOverload("", "base_class", "base_function", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, base_function_struct_B);
		overload->addOverload("", "base_class", "base_function", { std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, base_function_array);


		base_class_general_callback::overload = overload;
		Nan::SetPrototypeMethod(ctor, "base_function", base_class_general_callback::overload_callback);


		target->Set(Nan::New("base_class").ToLocalChecked(), ctor->GetFunction());

		overload->register_type(ctor,"", "base_class");
	};

	NAN_METHOD(base_class::New) {

		if (!info.IsConstructCall())
			return Nan::ThrowTypeError("Cannot call constructor as function");

		base_class *pt;

		pt = new base_class();

		pt->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}

	NAN_METHOD(base_class::base_function) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.no_parameters_testers").ToLocalChecked());
	}


	NAN_METHOD(base_class::base_function_number) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.number").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_string) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.string").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_bool) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.bool").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_date) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.date").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_function) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.function").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_buffer) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.buffer").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_map) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.map").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_set) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.set").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_promise) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.promise").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_proxy) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.proxy").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_regexp) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.regexp").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_base_class) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.base_class").ToLocalChecked());
	}
	NAN_METHOD(base_class::base_function_derived_class) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.derived_class").ToLocalChecked());
	}

	NAN_METHOD(base_class::base_function_struct_A) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.struct_A").ToLocalChecked());
	}

	NAN_METHOD(base_class::base_function_struct_B) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.struct_B").ToLocalChecked());
	}

	NAN_METHOD(base_class::base_function_array) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.array").ToLocalChecked());
	}
