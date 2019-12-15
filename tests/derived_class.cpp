#include "derived_class.h"

#include "base_class.h"

namespace derived_class_general_callback {
	std::shared_ptr<overload_resolution> overload;
	NAN_METHOD(overload_callback) {
		return overload->execute("", info);
	}
}

Nan::Persistent<v8::FunctionTemplate> derived_class::constructor;

void derived_class::Init(v8::Local<v8::Object> target, std::shared_ptr<overload_resolution> overload) {
	derived_class_general_callback::overload = overload;


	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(derived_class::New);
	constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("derived_class").ToLocalChecked());

	assert(!base_class::constructor.IsEmpty() && "must initialize base class before derived class!");
	ctor->Inherit(Nan::New(base_class::constructor));

	Nan::SetPrototypeMethod(ctor, "derived_function", derived_function, Nan::New("derived_function").ToLocalChecked());

	overload->addOverload("", "derived_class", "base_function", {}, base_function);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Number") }, base_function_number);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","String") }, base_function_string);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Boolean") }, base_function_bool);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Date") }, base_function_date);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Function") }, base_function_function);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Buffer") }, base_function_buffer);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Map") }, base_function_map);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Set") }, base_function_set);
#endif
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Promise") }, base_function_promise);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Proxy") }, base_function_proxy);
#endif
	overload->addOverload("", "derived_class", "base_function", { make_param("a","RegExp") }, base_function_regexp);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","base_class") }, base_function_base_class);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","derived_class") }, base_function_derived_class);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","struct_A") }, base_function_struct_A);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","struct_B") }, base_function_struct_B);
	overload->addOverload("", "derived_class", "base_function", { make_param("a","Array") }, base_function_array);


	Nan::SetPrototypeMethod(ctor, "this_check", derived_class_general_callback::overload_callback, Nan::New("this_check").ToLocalChecked());
	overload->addOverload("", "derived_class", "this_check", {}, this_check);
	
	
	Nan::Set(target,Nan::New("derived_class").ToLocalChecked(), Nan::GetFunction(ctor).ToLocalChecked());
	overload->register_type<derived_class>(ctor,"", "derived_class");
};

v8::Local<v8::Function> derived_class::get_constructor() {
	return Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
}

std::shared_ptr<derived_class> derived_class::New() {
	auto ret = std::make_shared<derived_class>();
	return ret;
}

NAN_METHOD(derived_class::New) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	derived_class *pt;

	pt = new derived_class();

	pt->Wrap(info.This());
	//info.GetReturnValue().Set(info.This());
}

POLY_METHOD(derived_class::this_check) {
	auto t = info.This<derived_class*>();

	if (info.is_async) {
		info.SetReturnValue(t != NULL);
	}
	else {
		auto unwrapped = overres::ObjectWrap::Unwrap<derived_class>(info.This());
		info.GetReturnValue().Set(Nan::New(t == unwrapped));
	}
}

NAN_METHOD(derived_class::derived_function) {
	info.GetReturnValue().Set(Nan::True());
}


POLY_METHOD(derived_class::base_function) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.no_parameters_testers").ToLocalChecked());
}


POLY_METHOD(derived_class::base_function_number) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.number").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_string) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.string").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_bool) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.bool").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_date) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.date").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_function) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.function").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_buffer) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.buffer").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_map) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.map").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_set) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.set").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_promise) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.promise").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_proxy) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.proxy").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_regexp) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.regexp").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_base_class) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.base_class").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_derived_class) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.derived_class").ToLocalChecked());
}
POLY_METHOD(derived_class::base_function_struct_A) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.struct_A").ToLocalChecked());
}

POLY_METHOD(derived_class::base_function_struct_B) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.struct_B").ToLocalChecked());
}

POLY_METHOD(derived_class::base_function_array) {
	info.GetReturnValue().Set(Nan::New<v8::String>("derived_class.base_function.array").ToLocalChecked());
}
