#ifndef _O_R_OVERLOAD_RESOLUTION_CLASS_WRAP_H_
#define _O_R_OVERLOAD_RESOLUTION_CLASS_WRAP_H_

#include "overload_executor.h"
#include "value_converter_base.h"

class class_wrap {
private:
	const v8::Local<v8::Object> _target;
	std::shared_ptr<overload_executor> _executor;
	const std::string _class;
	v8::Local<v8::FunctionTemplate> _ctor;

	Nan::PropertyGetterCallback _named_property_getter_instance;
	static NAN_PROPERTY_GETTER(named_property_getter_wrapper);
	
public:
	class_wrap(v8::Local<v8::Object> target, std::shared_ptr<overload_executor> executor, const std::string &&class_name);

	//when class definitions is done, this must be executed to hook the executor, namespace and register the class in the type system
	template<typename T>
	std::shared_ptr<overres::object_type> done() {
		auto ctor_func = Nan::GetFunction(_ctor).ToLocalChecked();

		Nan::SetPrivate(ctor_func, Nan::New("namespace").ToLocalChecked(), Nan::New(_class).ToLocalChecked());
		Nan::SetPrivate(ctor_func, Nan::New("executor").ToLocalChecked(), Nan::New<v8::External>(_executor.get()));
		Nan::SetPrivate(ctor_func, Nan::New("named_property_getter_instance").ToLocalChecked(), Nan::New<v8::External>((void*)_named_property_getter_instance));
		
		Nan::Set(_target,Nan::New(_class).ToLocalChecked(), ctor_func);
		return _executor->type_system.register_type<T>(_ctor,_class,_class);
		//return _ctor;
	}

	void add_overload_constructor(std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds an overload function
	void add_overload(const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds an overload for a static function
	void add_static_overload(const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds a property accessor
	void add_property(const std::string &&propertyName, Nan::GetterCallback getter, Nan::SetterCallback setter = 0, v8::Local<v8::Value> data = v8::Local<v8::Value>());

	//adds a numeric indexer
	void add_numeric_indexer(Nan::IndexGetterCallback getter, Nan::IndexSetterCallback setter = 0, Nan::IndexQueryCallback query = 0, Nan::IndexDeleterCallback deleter = 0
		, Nan::IndexEnumeratorCallback enumerator = 0, v8::Local<v8::Value> data = v8::Local<v8::Value>());

	//add a string indexer
	void add_named_indexer(Nan::PropertyGetterCallback getter, Nan::PropertySetterCallback setter = 0, Nan::PropertyQueryCallback query = 0, Nan::PropertyDeleterCallback deleter = 0
		, Nan::PropertyEnumeratorCallback enumerator = 0, v8::Local<v8::Value> data = v8::Local<v8::Value>());
};

#endif