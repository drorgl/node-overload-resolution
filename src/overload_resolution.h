#ifndef _ALVISION_OVERLOAD_RESOLUTION_H_
#define _ALVISION_OVERLOAD_RESOLUTION_H_

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_version.h>
#include <node_buffer.h>
#include <string.h>
#include <nan.h>

#include "overload_executor.h"

#include "namespace_wrap.h"
//#include "class_alias.h"


//#include <memory>
//#include <string>
//#include <vector>
//#include <functional>

/**
 * @defgroup overload_resolution Overload Resolution Function Overload Callback Resolution, determines best matches and automagically converts from/to V8 to C++ types
 */

/** 
 * @addtogroup overload_resolution
 * @{
 */

#define	POLY_METHOD(name)                                                       \
		Nan::NAN_METHOD_RETURN_TYPE name(POLY_METHOD_ARGS_TYPE info)





////overload resolution module
//
////on constructor, register each function signature and c++ function that implements it
////supply global callback for all functions
//

namespace overres {
	class function_arguments;

	template<typename T>
	std::shared_ptr<generic_value_holder> make_value(T value) {
		auto gvalue = std::make_shared<generic_value_holder>();
		gvalue->Set(std::make_shared < overres::value_converter<T>>(), std::make_shared < overres::value_holder<T>>(value));
		return gvalue;
	}
};


class overload_resolution {
private:
	//static void LogDebug(std::function<std::string()> message);
	//static void LogWarn(std::function<std::string()> message);

	std::shared_ptr<overload_executor> _executor;
public:
	overload_resolution();

	~overload_resolution();

	//function should be registerType
	//should add to it all the basics, string, number, integer, boolean, array, object(?), buffer (?), function (is it possible to know the function signature?), promises(?)
	//in case of array, which type is inside it, what to do if multiple types are in the array?
	template <typename TObjectWrap>
	void register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const std::string &&ns, const std::string &&name) {
		_executor->type_system.register_type<TObjectWrap>(functionTemplate, ns, name);
	}

	//register struct
	template <typename TDerived>
	void register_type(const std::string &&ns, const std::string &&name) {	
		_executor->type_system.register_type<TDerived>(std::move(ns),std::move(name));
	}

	//add type alias
	void add_type_alias(std::string &&alias, std::string &&type);

	bool validate_type_registrations();

	//adds an overload function
	void addOverload(const std::string &&ns, const std::string &&className, const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> &&arguments, PolyFunctionCallback callback);

	//adds an overload for a static function
	void addStaticOverload(const std::string &&ns, const std::string &&className, const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> &&arguments, PolyFunctionCallback callback);

	//adds an overload constructor
	void addOverloadConstructor(const std::string &&ns, const std::string &&className, std::vector<std::shared_ptr<overload_info>> &&arguments, PolyFunctionCallback callback);

	std::shared_ptr<namespace_wrap> register_module(v8::Local<v8::Object> target);



	inline std::string get_type(v8::Local<v8::Value> param) {
		return _executor->type_system.determineType(param);
	}


	//catch-all function, looks up the function in the overloads collections and executing the right one
	Nan::NAN_METHOD_RETURN_TYPE execute(const std::string &&name_space, Nan::NAN_METHOD_ARGS_TYPE info);
};

/** @}*/

#endif