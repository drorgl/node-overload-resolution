#ifndef _O_R_OVERLOAD_RESOLUTION_TYPES_H_
#define _O_R_OVERLOAD_RESOLUTION_TYPES_H_

#include <nan.h>
#include <unordered_map>
//#include "value_converter_base.h"
#include <memory>

//#include "overload_info.h"

#include "FunctionCallbackInfo.h"

//namespace overres {
//	template<typename T>
//	class FunctionCallbackInfo;
//}

/**
 * @brief polymorphic method argument type
 * 
 */
typedef const overres::FunctionCallbackInfo<v8::Value>& POLY_METHOD_ARGS_TYPE;

/**
 * @brief polymorphic function callback
 * 
 */
typedef void(*PolyFunctionCallback)(POLY_METHOD_ARGS_TYPE);

struct overload_info;

/**
 * @brief overload resolution function
 * 
 */
struct o_r_function {
	/**
	 * @brief function callback
	 * 
	 */
	PolyFunctionCallback function;
	/**
	 * @brief function name
	 * 
	 */
	std::string functionName;
	/**
	 * @brief class name
	 * 
	 */
	std::string className;

	/**
	 * @brief is function a constructor
	 * 
	 */
	bool is_constructor;

	/**
	 * @brief is function a static method
	 * 
	 */
	bool is_static;

	/**
	 * @brief function callback argument parameters
	 * 
	 */
	std::vector<std::shared_ptr<overload_info>> parameters;
};

/**
 * @brief overload resolution class
 * 
 */
struct o_r_class {
	/**
	 * @brief class name
	 * 
	 */
	std::string className;

	/**
	 * @brief class functions
	 * 
	 */
	std::unordered_map<std::string, std::vector<std::shared_ptr< o_r_function>>> functions;
};

/**
 * @brief overload resolution namespace
 * 
 */
struct o_r_namespace {
	/**
	 * @brief namespace name
	 * 
	 */
	std::string name;

	/**
	 * @brief namespace classes
	 * 
	 */
	std::unordered_map<std::string, std::shared_ptr< o_r_class>> classes;
};

#endif