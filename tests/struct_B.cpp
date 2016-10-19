#include "struct_B.h"

std::vector<std::shared_ptr<overload_info>> struct_B::_definition = { 
	std::make_shared<overload_info>("prop1","String",Nan::Undefined()) ,
	std::make_shared<overload_info>("prop2","Number",Nan::Undefined())
};


bool struct_B::verify(overload_resolution * ovres, v8::Local<v8::Value> obj) {
	return ovres->verifyObject(struct_B::_definition, obj);
}

bool struct_B::parse(overload_resolution * ovres, v8::Local<v8::Value> obj) {
	this->prop1 = *Nan::Utf8String(ovres->GetFromObject(obj, "prop1").ToLocalChecked());
	this->prop2 = ovres->GetFromObject(obj, "prop2").ToLocalChecked()->IntegerValue();

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