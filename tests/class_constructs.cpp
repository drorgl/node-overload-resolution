#include "class_constructs.h"

Nan::Persistent<v8::FunctionTemplate> class_constructs::constructor;

void class_constructs::Init(v8::Handle<v8::Object> target, std::shared_ptr<overload_resolution> overload) {
	auto ns = overload->add_namespace("tests");
	ns->
}


v8::Local<v8::Function> class_constructs::get_constructor() {

}

POLY_METHOD(class_constructs::New) {

}

POLY_METHOD(class_constructs::test_static) {

}

POLY_METHOD(class_constructs::test_member) {

}


