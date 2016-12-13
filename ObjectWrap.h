#ifndef _O_R_OBJECTWRAP_H_
#define _O_R_OBJECTWRAP_H_

#include <nan.h>

namespace or {
	class ObjectWrap : public Nan::ObjectWrap {
	public:
		ObjectWrap() : Nan::ObjectWrap() {}

		using Nan::ObjectWrap::Wrap;

		v8::Local<v8::Object> Wrap() {
			//if the object was already wrapped, returned the persistent object
			if (!this->persistent().IsEmpty()) {
				return Nan::New(this->persistent());
			}

			auto return_object = Nan::New<v8::Object>();
			this->Wrap(return_object);
			return return_object;
		}

		template <class T>
		static inline T* Unwrap(v8::Local<v8::Object> handle) {
			return Nan::ObjectWrap::Unwrap<T>(handle);
		}

		virtual ~ObjectWrap() {}

		
	};
}

#endif