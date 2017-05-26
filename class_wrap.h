#ifndef _O_R_OVERLOAD_RESOLUTION_CLASS_WRAP_H_
#define _O_R_OVERLOAD_RESOLUTION_CLASS_WRAP_H_

#include "overload_executor.h"
#include "value_converter_base.h"

class class_wrap {
private:
	v8::Handle<v8::Object> _target;
	overload_executor * _executor;
	std::string _class;
	v8::Local<v8::FunctionTemplate> _ctor;

public:
	class_wrap(v8::Handle<v8::Object> target, overload_executor * executor, const std::string class_name);

	//when class definitions is done, this must be executed to hook the executor, namespace and register the class in the type system
	template<typename T>
	v8::Local<v8::FunctionTemplate> done() {
		auto ctor_func = _ctor->GetFunction();

		Nan::SetPrivate(ctor_func, Nan::New("namespace").ToLocalChecked(), Nan::New(_class).ToLocalChecked());
		Nan::SetPrivate(ctor_func, Nan::New("executor").ToLocalChecked(), Nan::New<v8::External>(_executor));

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