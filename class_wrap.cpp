#include "class_wrap.h"

static void class_callback_function(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	//if executing member callback
	auto this_ = info.This();
	auto prototype = Nan::To<v8::Object>(this_->GetPrototype()).ToLocalChecked();
	auto holder = Nan::To<v8::Function>(Nan::Get(prototype,Nan::New("constructor").ToLocalChecked()).ToLocalChecked()).ToLocalChecked();

	auto executor_object = Nan::GetPrivate(holder, Nan::New("executor").ToLocalChecked());
	if (executor_object.IsEmpty()) {
		Nan::ThrowError("executor is empty, this object is not part of overload resolution");
		return;
	}

	auto executor = (overload_executor * )executor_object.ToLocalChecked().As<v8::External>()->Value();

	//if executor is empty then its a static member callback
	if (executor == NULL) {

		auto static_holder = info.Holder();
		holder = static_holder.As<v8::Function>();
		executor = (overload_executor *)Nan::GetPrivate(holder, Nan::New("executor").ToLocalChecked()).ToLocalChecked().As<v8::External>()->Value();

		if (executor == NULL) {
			Nan::ThrowError("executor holder is not set, this object is not part of overload resolution");
			return;
		}
	}


	auto ns = Nan::GetPrivate(holder, Nan::New("namespace").ToLocalChecked());
	executor->execute(*Nan::Utf8String(ns.ToLocalChecked()), info);
}

class_wrap::class_wrap(v8::Local<v8::Object> target, overload_executor * executor, const std::string &&class_name):
	_target (target),
	_class (class_name){
	_executor = executor;

	_ctor = Nan::New<v8::FunctionTemplate>(class_callback_function);
	_ctor->InstanceTemplate()->SetInternalFieldCount(1);
	_ctor->SetClassName(Nan::New(_class).ToLocalChecked());
}

void class_wrap::add_overload_constructor(std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addOverloadConstructor(_class, _class, arguments, callback);
}

void class_wrap::add_overload(const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addOverload(_class, _class, functionName, arguments, callback);
	Nan::SetPrototypeMethod(_ctor, functionName.c_str(), class_callback_function,Nan::New(functionName.c_str()).ToLocalChecked());
}

void class_wrap::add_static_overload(const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addStaticOverload(_class, _class, functionName, arguments, callback);
	Nan::SetMethod(_ctor, functionName.c_str(), class_callback_function,Nan::New(functionName).ToLocalChecked());
}

void class_wrap::add_property(const std::string &&propertyName, Nan::GetterCallback getter, Nan::SetterCallback setter, v8::Local<v8::Value> data){
	Nan::SetAccessor(_ctor->InstanceTemplate(),Nan::New( propertyName).ToLocalChecked(), getter, setter,data);
}

void class_wrap::add_numeric_indexer(Nan::IndexGetterCallback getter, Nan::IndexSetterCallback setter, Nan::IndexQueryCallback query, Nan::IndexDeleterCallback deleter
	, Nan::IndexEnumeratorCallback enumerator, v8::Local<v8::Value> data){
	Nan::SetIndexedPropertyHandler(_ctor->InstanceTemplate(), getter, setter,query,deleter,enumerator,data);
}

NAN_PROPERTY_GETTER(class_wrap::named_property_getter_wrapper) {
	auto real_property = Nan::GetRealNamedProperty(info.This(),property);
	if (!real_property.IsEmpty()) {
		info.GetReturnValue().Set(real_property.ToLocalChecked());
		return;
	}

	auto this_ = info.This();
	auto prototype = Nan::To<v8::Object>(this_->GetPrototype()).ToLocalChecked();
	auto holder = Nan::To<v8::Function>(Nan::Get(prototype,Nan::New("constructor").ToLocalChecked()).ToLocalChecked()).ToLocalChecked();

	auto named_property_getter_instance_object = Nan::GetPrivate(holder, Nan::New("named_property_getter_instance").ToLocalChecked());
	if (!named_property_getter_instance_object.IsEmpty()) {
		auto named_property_getter_instance_object_executor = (Nan::PropertyGetterCallback)named_property_getter_instance_object.ToLocalChecked().As<v8::External>()->Value();
		if (named_property_getter_instance_object_executor != NULL) {
			named_property_getter_instance_object_executor(property, info);
		}
	}
}

void class_wrap::add_named_indexer(Nan::PropertyGetterCallback getter, Nan::PropertySetterCallback setter, Nan::PropertyQueryCallback query, Nan::PropertyDeleterCallback deleter
	, Nan::PropertyEnumeratorCallback enumerator, v8::Local<v8::Value> data) {

	_named_property_getter_instance = getter;

	Nan::SetNamedPropertyHandler(_ctor->InstanceTemplate(), named_property_getter_wrapper, setter, query, deleter, enumerator, data);
}