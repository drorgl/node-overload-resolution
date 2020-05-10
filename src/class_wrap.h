#ifndef _O_R_OVERLOAD_RESOLUTION_CLASS_WRAP_H_
#define _O_R_OVERLOAD_RESOLUTION_CLASS_WRAP_H_

#include "overload_executor.h"
#include "value_converter_base.h"

/** 
 * @addtogroup overload_resolution
 * @{
 */

/**
 * @brief class wrap for wrapping class resolution functionality
 * 
 */
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

	/**
	 * @brief add constructor
	 * 
	 * @param arguments a list of unique arguments for the constructor
	 * @param callback POLY_METHOD callback that executes when the constructor is called
	 */
	void add_overload_constructor(std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	/**
	 * @brief adds an instance function
	 * 
	 * @param functionName the member function name
	 * @param arguments a list of unique arguments for the member function
	 * @param callback POLY_METHOD callback that executes when the member function is called
	 */
	void add_overload(const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	/**
	 * @brief adds static function
	 * 
	 * @param functionName the static function name
	 * @param arguments a list of unique arguments for the static function
	 * @param callback POLY_METHOD callback that executes when the static function is called
	 */
	void add_static_overload(const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	/**
	 * @brief adds a property accessor
	 * 
	 * @param propertyName the member property name
	 * @param getter NAN_GETTER callback that executes when the property getter is called
	 * @param setter NAN_SETTER callback that executes when the property setter is called
	 * @param data data for passing into the callback methods
	 */
	void add_property(const std::string &&propertyName, Nan::GetterCallback getter, Nan::SetterCallback setter = 0, v8::Local<v8::Value> data = v8::Local<v8::Value>());

	/**
	 * @brief adds a numeric indexer
	 * i.e indexer[0]
	 * 
	 * @param getter NAN_INDEX_GETTER callback that executes when the numeric getter is called
	 * @param setter NAN_INDEX_SETTER callback that executes when the numeric setter is called
	 * @param query NAN_INDEX_QUERY callback that executes when the object query is called
	 * @param deleter NAN_INDEX_DELETER callback that executes when the object deleter is called
	 * @param enumerator NAN_INDEX_ENUMERATOR callback that executes when the object enumerator is called
	 * @param data data for passing into the callback methods
	 */
	void add_numeric_indexer(Nan::IndexGetterCallback getter, Nan::IndexSetterCallback setter = 0, Nan::IndexQueryCallback query = 0, Nan::IndexDeleterCallback deleter = 0
		, Nan::IndexEnumeratorCallback enumerator = 0, v8::Local<v8::Value> data = v8::Local<v8::Value>());

	/**
	 * @brief add a string indexer
	 * 
	 * @param getter NAN_PROPERTY_GETTER callback that executes when the named getter is called
	 * @param setter NAN_PROPERTY_SETTER callback that executes when the named setter is called
	 * @param query NAN_PROPERTY_QUERY callback that executes when the property query is called
	 * @param deleter NAN_PROPERTY_DELETER callback that executes when the property deleter is called
	 * @param enumerator NAN_PROPERTY_ENUMERATOR callback that executes when the object enumerator is called
	 * @param data data for passing into the callback methods
	 */
	void add_named_indexer(Nan::PropertyGetterCallback getter, Nan::PropertySetterCallback setter = 0, Nan::PropertyQueryCallback query = 0, Nan::PropertyDeleterCallback deleter = 0
		, Nan::PropertyEnumeratorCallback enumerator = 0, v8::Local<v8::Value> data = v8::Local<v8::Value>());
};

/** @}*/

#endif