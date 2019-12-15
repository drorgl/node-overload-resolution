#include "namespace_wrap.h"

#include <functional>
#include <nan.h>

static void ns_callback_function(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	auto holder = info.Holder();
	auto executor = (overload_executor *)Nan::GetPrivate(holder, Nan::New("executor").ToLocalChecked()).ToLocalChecked().As<v8::External>()->Value();

	if (executor == NULL) {
		Nan::ThrowError("executor is not set, holder object is not part of overload resolution");
		return;
	}

	auto ns = Nan::GetPrivate(holder, Nan::New("namespace").ToLocalChecked());
	executor->execute(*Nan::Utf8String(ns.ToLocalChecked()), info);
}

namespace_wrap::namespace_wrap(v8::Handle<v8::Object> target, overload_executor * executor, const std::string &&ns):
	_namespace(ns){
	if (ns != "") {
		_target = Nan::New<v8::Object>();
		target->Set(Nan::New(ns).ToLocalChecked(), _target);
	}
	else {
		_target = target;
	}

	Nan::SetPrivate(_target, Nan::New("executor").ToLocalChecked(), Nan::New<v8::External>(executor));
	Nan::SetPrivate(_target, Nan::New("namespace").ToLocalChecked(), Nan::New(_namespace).ToLocalChecked());

	_executor = executor;
}

std::shared_ptr<namespace_wrap> namespace_wrap::add_namespace(const std::string && namespace_name) {
	return std::make_shared<namespace_wrap>(_target, _executor, std::move(namespace_name));
}

std::shared_ptr<class_wrap> namespace_wrap::add_class(const std::string &&class_name) {
	return std::make_shared<class_wrap>(_target, _executor, std::move(class_name));
}


void namespace_wrap::add_overload(const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	//Nan::SetMethod(_target, functionName.c_str(), std::bind(_executor->execute(_namespace)));
	//auto bb = std::bind(&namespace_alias::_ns_callback, this, std::placeholders::_1);
	_executor->type_system.addOverload(_namespace, "", functionName, arguments, callback);

	Nan::SetMethod(_target, functionName.c_str(), ns_callback_function, Nan::New(functionName.c_str()).ToLocalChecked());
}

void namespace_wrap::add_enum(const std::string &&enumName, std::vector<std::pair<std::string, double>> values) {
	auto obj = Nan::New<v8::Object>();
	_target->Set(Nan::New(enumName).ToLocalChecked(), obj);

	for (auto value : values) {
		obj->Set(Nan::New(value.first).ToLocalChecked(), Nan::New(value.second));
	}
}