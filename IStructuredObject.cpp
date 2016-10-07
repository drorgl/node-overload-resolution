#include "IStructuredObject.h"

bool IStructuredObject::parse(v8::Local<v8::Value> obj) {
	return false;
}

v8::Local<v8::Value> IStructuredObject::ToObject() {
	return Nan::Null();
}
