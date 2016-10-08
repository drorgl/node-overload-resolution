#include "struct_A.h"

std::vector<std::shared_ptr<overload_info>> struct_A::_definition = { 
	std::make_shared<overload_info>("prop1","String",Nan::Undefined()) ,
	std::make_shared<overload_info>("prop2","String",Nan::Undefined())
};


bool struct_A::verify(overload_resolution * ovres, v8::Local<v8::Value> obj) {
	return ovres->verifyObject(struct_A::_definition, obj);
}

bool struct_A::parse(overload_resolution * ovres, v8::Local<v8::Value> obj) {
	this->prop1 = *Nan::Utf8String(ovres->GetFromObject(obj, "prop1").ToLocalChecked());
	this->prop2 = *Nan::Utf8String(ovres->GetFromObject(obj, "prop2").ToLocalChecked());

	return true;
}


v8::Local<v8::Value> struct_A::ToObject() {
	return Nan::Undefined();
}