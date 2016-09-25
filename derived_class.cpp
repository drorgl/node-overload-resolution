#include "derived_class.h"

#include "base_class.h"

Nan::Persistent<FunctionTemplate> derived_class::constructor;

void derived_class::Init(Handle<Object> target, std::shared_ptr<overload_resolution> overload) {
	Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(derived_class::New);
	constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("derived_class").ToLocalChecked());

	assert(!base_class::constructor.IsEmpty() && "must initialize base class before derived class!");
	ctor->Inherit(Nan::New(base_class::constructor));

	Nan::SetPrototypeMethod(ctor, "derived_function", derived_function);

	target->Set(Nan::New("derived_class").ToLocalChecked(), ctor->GetFunction());
	overload->register_type(ctor, "derived_class");
};

NAN_METHOD(derived_class::New) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	derived_class *pt;

	pt = new derived_class();

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

NAN_METHOD(derived_class::derived_function) {
	info.GetReturnValue().Set(Nan::True());
}