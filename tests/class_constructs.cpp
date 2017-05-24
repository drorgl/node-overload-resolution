#include "class_constructs.h"

Nan::Persistent<v8::FunctionTemplate> class_constructs::constructor;

void class_constructs::Init(std::shared_ptr<namespace_alias> overload) {
	auto class_def = overload->add_class("class_constructs");
	class_def->add_overload_constructor({}, New);
	class_def->add_static_overload("test_static", {}, test_static);
	class_def->add_overload("test_member", {}, test_member);
}


v8::Local<v8::Function> class_constructs::get_constructor() {
	return Nan::New(constructor)->GetFunction();
}

POLY_METHOD(class_constructs::New) {
	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	class_constructs *pt;

	pt = new class_constructs();

	pt->Wrap(info.This());
	//info.GetReturnValue().Set(info.This());
}

POLY_METHOD(class_constructs::test_static) {
	info.SetReturnValue("test_static"s);
}

POLY_METHOD(class_constructs::test_member) {
	info.SetReturnValue("test_member"s);
}


