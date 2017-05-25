#ifndef _O_R_OVERLOAD_RESOLUTION_CLASS_ALIAS_H_
#define _O_R_OVERLOAD_RESOLUTION_CLASS_ALIAS_H_

#include "overload_executor.h"
#include "value_converter_base.h"

class class_alias {
private:
	v8::Handle<v8::Object> _target;
	std::shared_ptr<overload_executor> _executor;
	std::string _class;
	v8::Local<v8::FunctionTemplate> _ctor;

public:
	class_alias(v8::Handle<v8::Object> target, std::shared_ptr<overload_executor> executor, const std::string class_name);

	template<typename T>
	Nan::Persistent<v8::FunctionTemplate> done() {
		auto ctor_func = _ctor->GetFunction();

		Nan::SetPrivate(ctor_func, Nan::New("namespace").ToLocalChecked(), Nan::New(_class).ToLocalChecked());
		Nan::SetPrivate(ctor_func, Nan::New("executor").ToLocalChecked(), Nan::New<v8::External>(new std::shared_ptr<overload_executor>(_executor)));

		_target->Set(Nan::New(_class).ToLocalChecked(), ctor_func);
		_executor->type_system.register_type<T>(_ctor,_class,_class);
		return _ctor;
	}

	void add_overload_constructor(std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds an overload function
	void add_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds an overload for a static function
	void add_static_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);
};

#endif