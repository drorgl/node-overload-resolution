#include "base_class.h"


namespace base_class_general_callback {
	std::shared_ptr<overload_resolution> overload;
	NAN_METHOD(overload_callback) {
		return overload->execute("", info);
	}
}

	Nan::Persistent<v8::FunctionTemplate> base_class::constructor;

	void base_class::Init(v8::Local<v8::Object> target, std::shared_ptr<overload_resolution> overload) {
		v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(base_class::New);
		constructor.Reset(ctor);
		ctor->InstanceTemplate()->SetInternalFieldCount(1);
		ctor->SetClassName(Nan::New("base_class").ToLocalChecked());

		//Nan::SetPrototypeMethod(ctor, "base_function", base_function);

		overload->addOverload("", "base_class","base_function", {}, base_function);
		overload->addOverload("", "base_class","base_function", { make_param("a","Number",Nan::Undefined()) }, base_function_number);
		overload->addOverload("", "base_class","base_function", { make_param("a","String",Nan::Undefined()) }, base_function_string);
		overload->addOverload("", "base_class","base_function", { make_param("a","Boolean",Nan::Undefined()) }, base_function_bool);
		overload->addOverload("", "base_class","base_function", { make_param("a","Date",Nan::Undefined()) }, base_function_date);
		overload->addOverload("", "base_class","base_function", { make_param("a","Function",Nan::Undefined()) }, base_function_function);
		overload->addOverload("", "base_class","base_function", { make_param("a","Buffer",Nan::Undefined()) }, base_function_buffer);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("", "base_class","base_function", { make_param("a","Map",Nan::Undefined()) }, base_function_map);
		overload->addOverload("", "base_class","base_function", { make_param("a","Set",Nan::Undefined()) }, base_function_set);
#endif
		overload->addOverload("", "base_class","base_function", { make_param("a","Promise",Nan::Undefined()) }, base_function_promise);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("", "base_class","base_function", { make_param("a","Proxy",Nan::Undefined()) }, base_function_proxy);
#endif
		overload->addOverload("", "base_class","base_function", { make_param("a","RegExp",Nan::Undefined()) }, base_function_regexp);
		overload->addOverload("", "base_class","base_function", { make_param("a","base_class",Nan::Undefined()) }, base_function_base_class);
		overload->addOverload("", "base_class","base_function", { make_param("a","derived_class",Nan::Undefined()) }, base_function_derived_class);
		overload->addOverload("", "base_class","base_function", { make_param("a","struct_A",Nan::Undefined()) },      base_function_struct_A);
		overload->addOverload("", "base_class", "base_function", { make_param("a","struct_B",Nan::Undefined()) }, base_function_struct_B);
		overload->addOverload("", "base_class", "base_function", { make_param("a","Array",Nan::Undefined()) }, base_function_array);


		base_class_general_callback::overload = overload;
		Nan::SetPrototypeMethod(ctor, "base_function", base_class_general_callback::overload_callback, Nan::New("base_function").ToLocalChecked());

		Nan::Set(target,Nan::New("base_class").ToLocalChecked(),Nan::GetFunction(ctor).ToLocalChecked());

		overload->register_type<base_class>(ctor,"", "base_class");
	};

	 v8::Local<v8::Function> base_class::get_constructor() {
		return Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
	}

	 std::shared_ptr<base_class> base_class::New() {
		auto ret = std::make_shared<base_class>();
		return ret;
	}

	NAN_METHOD(base_class::New) {

		if (!info.IsConstructCall())
			return Nan::ThrowTypeError("Cannot call constructor as function");

		base_class *pt;

		pt = new base_class();

		pt->Wrap(info.This());
		//info.GetReturnValue().Set(info.This());
	}

	POLY_METHOD(base_class::base_function) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.no_parameters_testers").ToLocalChecked());
	}


	POLY_METHOD(base_class::base_function_number) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.number").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_string) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.string").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_bool) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.bool").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_date) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.date").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_function) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.function").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_buffer) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.buffer").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_map) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.map").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_set) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.set").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_promise) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.promise").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_proxy) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.proxy").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_regexp) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.regexp").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_base_class) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.base_class").ToLocalChecked());
	}
	POLY_METHOD(base_class::base_function_derived_class) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.derived_class").ToLocalChecked());
	}

	POLY_METHOD(base_class::base_function_struct_A) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.struct_A").ToLocalChecked());
	}

	POLY_METHOD(base_class::base_function_struct_B) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.struct_B").ToLocalChecked());
	}

	POLY_METHOD(base_class::base_function_array) {
		info.GetReturnValue().Set(Nan::New<v8::String>("base_class.base_function.array").ToLocalChecked());
	}
