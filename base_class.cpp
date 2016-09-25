#include "base_class.h"

	Nan::Persistent<FunctionTemplate> base_class::constructor;

	void base_class::Init(Handle<Object> target, std::shared_ptr<overload_resolution> overload) {
		Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(base_class::New);
		constructor.Reset(ctor);
		ctor->InstanceTemplate()->SetInternalFieldCount(1);
		ctor->SetClassName(Nan::New("base_class").ToLocalChecked());

		Nan::SetPrototypeMethod(ctor, "base_function", base_function);

		target->Set(Nan::New("base_class").ToLocalChecked(), ctor->GetFunction());

		overload->register_type(ctor, "base_class");
	};

	NAN_METHOD(base_class::New) {

		if (!info.IsConstructCall())
			return Nan::ThrowTypeError("Cannot call constructor as function");

		base_class *pt;

		pt = new base_class();

		pt->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}

	NAN_METHOD(base_class::base_function) {
		info.GetReturnValue().Set(Nan::True());
	}


