#include "ObjectWrap.h"

namespace or {

	v8::Local<v8::Object> ObjectWrap::Wrap() {
		//if the object was already wrapped, returned the persistent object
		if (!this->persistent().IsEmpty()) {
			return Nan::New(this->persistent());
		}

		auto return_object = get_constructor()->NewInstance();
		//auto return_object = Nan::New<v8::Object>();
		//return_object->InternalFieldCount ->SetInternalFieldCount(1)
		this->Wrap(return_object);
		return return_object;
	}
}