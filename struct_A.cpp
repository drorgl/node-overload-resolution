#include "struct_A.h"

bool struct_A::parse(v8::Local<v8::Value> obj) {
	if (obj->IsObject() || obj->IsMap()) {
		auto o = obj.As<v8::Object>();
		this->prop1 = *Nan::Utf8String (o->Get(Nan::New<v8::String>("prop1").ToLocalChecked()));
		this->prop2 = *Nan::Utf8String(o->Get(Nan::New<v8::String>("prop2").ToLocalChecked()));
	}


	return false;
}

v8::Local<v8::Value> struct_A::ToObject() {
	return Nan::Undefined();
}