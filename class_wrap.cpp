#include "class_wrap.h"

static void class_callback_function(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	auto this_ = info.This();
	
	auto constructor_name = this_->GetConstructorName();

	auto cn = *Nan::Utf8String(constructor_name);

	auto holder = this_->GetPrototype().As<v8::Object>()->Get(Nan::New("constructor").ToLocalChecked()).As<v8::Function>();

	auto executor_object = Nan::GetPrivate(holder, Nan::New("executor").ToLocalChecked());

	if (executor_object.IsEmpty()) {
		Nan::ThrowError("executor is empty, this object is not part of overload resolution");
		return;
	}

	auto executor = (std::shared_ptr<overload_executor>*)executor_object.ToLocalChecked().As<v8::External>()->Value();

	if (executor == NULL) {

		auto static_holder = info.Holder();

		constructor_name = static_holder->GetConstructorName();

		cn = *Nan::Utf8String(constructor_name);

		holder = static_holder.As<v8::Function>();
		executor = (std::shared_ptr<overload_executor>*)Nan::GetPrivate(holder, Nan::New("executor").ToLocalChecked()).ToLocalChecked().As<v8::External>()->Value();

		if (executor == NULL) {
			Nan::ThrowError("executor holder is not set, this object is not part of overload resolution");
			return;
		}


		
	}

	auto ns = Nan::GetPrivate(holder, Nan::New("namespace").ToLocalChecked());
	executor->get()->execute(*Nan::Utf8String(ns.ToLocalChecked()), info);
}

class_wrap::class_wrap(v8::Handle<v8::Object> target, std::shared_ptr<overload_executor> executor, const std::string class_name) {
	_target = target;
	_executor = executor;
	_class = class_name;

	_ctor = Nan::New<v8::FunctionTemplate>(class_callback_function);
	_ctor->InstanceTemplate()->SetInternalFieldCount(1);
	_ctor->SetClassName(Nan::New(_class).ToLocalChecked());
	
	
	
}

void class_wrap::add_overload_constructor(std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addOverloadConstructor(_class, _class, arguments, callback);
}

//adds an overload function
void class_wrap::add_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addOverload(_class, _class, functionName, arguments, callback);
	Nan::SetPrototypeMethod(_ctor, functionName.c_str(), class_callback_function);
}

//adds an overload for a static function
void class_wrap::add_static_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addStaticOverload(_class, _class, functionName, arguments, callback);
	Nan::SetMethod(_ctor, functionName.c_str(), class_callback_function);
}