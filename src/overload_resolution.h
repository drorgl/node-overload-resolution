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
 * @defgroup overload_resolution Overload Resolution Function Overload Callback Resolution
 */

/** 
 * @addtogroup overload_resolution
 * @{
 */


/**
 * @brief This is the method definition for polymorphic function names in Overload Resolution
 * 
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

	/**
	 * @brief Create an overload resolution value from C++ type value
	 * 
	 * @tparam T type of value
	 * @param value the value
	 * @return std::shared_ptr<generic_value_holder> generic value holder instance
	 */
	template<typename T>
	std::shared_ptr<generic_value_holder> make_value(T value) {
		auto gvalue = std::make_shared<generic_value_holder>();
		gvalue->Set(std::make_shared < overres::value_converter<T>>(), std::make_shared < overres::value_holder<T>>(value));
		return gvalue;
	}
};

/**
 * @brief Method Overload Resolution
 * Registers types and determine the best function call based on passed argument types
 * 
 */
class overload_resolution {
private:
	std::shared_ptr<overload_executor> _executor;
public:

	/**
	 * @brief Construct a new overload resolution instance
	 * @note only one instance is needed
	 * 
	 */
	overload_resolution();

	~overload_resolution();

	/**
	 * @brief register class types
	 * 
	 * @tparam TObjectWrap derived class from ObjectWrap
	 * @param functionTemplate the function template for the class
	 * @param ns the namespace
	 * @param name the name of the class
	 */
	template <typename TObjectWrap>
	void register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const std::string &&ns, const std::string &&name) {
		_executor->type_system.register_type<TObjectWrap>(functionTemplate, ns, name);
	}

	/**
	 * @brief register struct
	 * 
	 * @tparam TDerived derived struct from IStructuredObject
	 * @param ns the namespace
	 * @param name the struct name
	 */
	template <typename TDerived>
	void register_type(const std::string &&ns, const std::string &&name) {	
		_executor->type_system.register_type<TDerived>(std::move(ns),std::move(name));
	}

	/**
	 * @brief add type alias
	 * 
	 * @param alias the alias to add
	 * @param type for type, i.e. number, string, etc'
	 */
	void add_type_alias(std::string &&alias, std::string &&type);

	/**
	 * @brief Validates the registered type system such as missing types that were declared as function parameters
	 * 
	 * @return true if the type system is valid
	 * @return false if the type system is invalid
	 */
	bool validate_type_registrations();

	/**
	 * @brief adds an overload function
	 * 
	 * @param ns namespace of the function
	 * @param className the class name
	 * @param functionName the function name
	 * @param arguments argument types for the function
	 * @param callback the POLY_METHOD callback function
	 */
	void addOverload(const std::string &&ns, const std::string &&className, const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> &&arguments, PolyFunctionCallback callback);

	/**
	 * @brief adds an overload for a static function
	 * 
	 * @param ns namespace of the function
	 * @param className the class name
	 * @param functionName the function name
	 * @param arguments argument types for the function
	 * @param callback the POLY_METHOD callback function
	 */
	void addStaticOverload(const std::string &&ns, const std::string &&className, const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> &&arguments, PolyFunctionCallback callback);

	/**
	 * @brief adds an overload constructor
	 * 
	 * @param ns namespace of the function
	 * @param className the class name
	 * @param arguments argument types for the function
	 * @param callback the POLY_METHOD callback function
	 */
	void addOverloadConstructor(const std::string &&ns, const std::string &&className, std::vector<std::shared_ptr<overload_info>> &&arguments, PolyFunctionCallback callback);

	/**
	 * @brief Registers the Overload Resolution in Node.JS module
	 * @note this function should be called only once in the init of NODE_MODULE
	 * 
	 * @param target init function v8 object target 
	 * @return std::shared_ptr<namespace_wrap> returned initial namespace
	 */
	std::shared_ptr<namespace_wrap> register_module(v8::Local<v8::Object> target);


	/**
	 * @brief Get the type from overload resolution by v8 value
	 * @note this function can be used to retrieve primitives as well as registered types
	 * 
	 * @param param v8 value
	 * @return std::string type name
	 */
	inline std::string get_type(v8::Local<v8::Value> param) {
		return _executor->type_system.determineType(param);
	}


	/**
	 * @brief catch-all function, looks up the function in the overloads collections and executing the right one
	 * 
	 * @param name_space current namespace
	 * @param info function arguments
	 * @return Nan::NAN_METHOD_RETURN_TYPE return value from called function
	 */
	Nan::NAN_METHOD_RETURN_TYPE execute(const std::string &&name_space, Nan::NAN_METHOD_ARGS_TYPE info);
};

/** @}*/

#endif