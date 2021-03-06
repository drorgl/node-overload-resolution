#include "struct_A.h"

std::vector<std::shared_ptr<overload_info>> struct_A::_definition = { 
	make_param("prop1","String") ,
	make_param("prop2","String")
};


bool struct_A::verify(overres::type_system * ovres, v8::Local<v8::Value> obj) {
	return ovres->verifyObject(struct_A::_definition, obj);
}

bool struct_A::parse(v8::Local<v8::Value> obj) {
	this->prop1 = *Nan::Utf8String(overres::type_system::GetFromObject(obj, "prop1").ToLocalChecked());
	this->prop2 = *Nan::Utf8String(overres::type_system::GetFromObject(obj, "prop2").ToLocalChecked());

	return true;
}


v8::Local<v8::Value> struct_A::ToObject() {
	auto retval = Nan::New<v8::Object>();
	Nan::Set(retval,Nan::New<v8::String>("prop1").ToLocalChecked(), Nan::New<v8::String>(this->prop1).ToLocalChecked());
	Nan::Set(retval,Nan::New<v8::String>("prop2").ToLocalChecked(), Nan::New<v8::String>(this->prop2).ToLocalChecked());
	return retval;
}

v8::Local<v8::Object> struct_A::New() {
	auto a = std::make_shared<struct_A>();// a;
	return a->ToObject().As<v8::Object>();
}


v8::Local<v8::Object> struct_A::New(std::string &&prop1, std::string &&prop2) {
	auto a = std::make_shared<struct_A>();// a;
	a->prop1 = prop1;
	a->prop2 = prop2;
	return a->ToObject().As<v8::Object>();
}
