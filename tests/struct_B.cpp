#include "struct_B.h"

std::vector<std::shared_ptr<overload_info>> struct_B::_definition = { 
	make_param("prop1","String") ,
	make_param("prop2","Number")
};


bool struct_B::verify(overload_resolution * ovres, v8::Local<v8::Value> obj) {
	return ovres->verifyObject(struct_B::_definition, obj);
}

bool struct_B::parse(v8::Local<v8::Value> obj) {
	this->prop1 = *Nan::Utf8String(overload_resolution::GetFromObject(obj, "prop1").ToLocalChecked());
	this->prop2 = overload_resolution::GetFromObject(obj, "prop2").ToLocalChecked()->IntegerValue();

	return true;
}


v8::Local<v8::Value> struct_B::ToObject() {
	auto retval = Nan::New<v8::Object>();
	retval->Set(Nan::New<v8::String>("prop1").ToLocalChecked(), Nan::New<v8::String>(this->prop1).ToLocalChecked());
	retval->Set(Nan::New<v8::String>("prop2").ToLocalChecked(), Nan::New<v8::Number>(this->prop2));
	return retval;
}

v8::Local<v8::Object> struct_B::New() {
	struct_B b;
	return b.ToObject().As<v8::Object>();
}

v8::Local<v8::Object> struct_B::New(std::string prop1, int prop2) {
	struct_B b;
	b.prop1 = prop1;
	b.prop2 = prop2;
	return b.ToObject().As<v8::Object>();
}