#include "class_constructs.h"

Nan::Persistent<v8::FunctionTemplate> class_constructs::constructor;

void class_constructs::Init(std::shared_ptr<namespace_wrap> overload) {
	auto class_def = overload->add_class("class_constructs");
	class_def->add_overload_constructor({}, New);
	class_def->add_static_overload("test_static", {}, test_static);
	class_def->add_overload("test_member", {}, test_member);
	
	class_def->add_property("test_property", test_property_getter, test_property_setter);

	class_def->add_named_indexer(test_named_index_getter, test_named_index_setter);

	class_def->add_numeric_indexer(test_index_getter, test_index_setter);

	constructor.Reset(class_def->done<class_constructs>());

	overload->add_enum("test_enum", {
		{"e1", 1},
		{"e2",2}
	});
}


v8::Local<v8::Function> class_constructs::get_constructor() {
	return Nan::GetFunction(Nan::New(constructor)).ToLocalChecked();
}

POLY_METHOD(class_constructs::New) {
	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	class_constructs *pt;

	pt = new class_constructs();

	pt->_test_property = "preset_value";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(class_constructs::test_static) {
	info.SetReturnValue("test_static"s);
}

POLY_METHOD(class_constructs::test_member) {
	info.SetReturnValue("test_member"s);
}

NAN_GETTER(class_constructs::test_property_getter) {
	class_constructs* interceptor = ObjectWrap::Unwrap<class_constructs>(info.Holder());

	printf("class_constructs::test_property_getter\r\n");
	auto value = interceptor->_test_property;
	info.GetReturnValue().Set(Nan::New(value).ToLocalChecked());
}
NAN_SETTER(class_constructs::test_property_setter) {
	class_constructs* interceptor = ObjectWrap::Unwrap<class_constructs>(info.Holder());
	printf("class_constructs::test_property_setter\r\n");
	interceptor->_test_property = *Nan::Utf8String(value);
}

NAN_PROPERTY_GETTER(class_constructs::test_named_index_getter) {
	class_constructs* interceptor = ObjectWrap::Unwrap<class_constructs>(info.Holder());
	printf("class_constructs::test_named_index_getter\r\n");
	auto property_name = *Nan::Utf8String(property);

	if (interceptor->_test_string_indexer.find(property_name) == std::end(interceptor->_test_string_indexer)) {
		info.GetReturnValue().SetNull();
		return;
	}

	auto value = interceptor->_test_string_indexer[property_name];

	info.GetReturnValue().Set(Nan::New(value).ToLocalChecked());
}
NAN_PROPERTY_SETTER(class_constructs::test_named_index_setter) {
	class_constructs* interceptor = ObjectWrap::Unwrap<class_constructs>(info.Holder());
	printf("class_constructs::test_named_index_setter\r\n");
	auto property_name = *Nan::Utf8String(property);

	interceptor->_test_string_indexer[property_name] = *Nan::Utf8String(value);
}

NAN_INDEX_GETTER(class_constructs::test_index_getter) {
	class_constructs* interceptor = ObjectWrap::Unwrap<class_constructs>(info.Holder());
	printf("class_constructs::test_index_getter\r\n");
	if (interceptor->_test_numeric_indexer.find(index) == std::end(interceptor->_test_numeric_indexer)) {
		info.GetReturnValue().SetNull();
		return;
	}

	auto value = interceptor->_test_numeric_indexer[index];
	info.GetReturnValue().Set(Nan::New(value).ToLocalChecked());
}
NAN_INDEX_SETTER(class_constructs::test_index_setter) {
	class_constructs* interceptor = ObjectWrap::Unwrap<class_constructs>(info.Holder());
	printf("class_constructs::test_index_setter\r\n");
	interceptor->_test_numeric_indexer[index] = *Nan::Utf8String(value);
}
