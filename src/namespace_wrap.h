#ifndef _O_R_OVERLOAD_RESOLUTION_NAMESPACE_WRAP_H_
#define _O_R_OVERLOAD_RESOLUTION_NAMESPACE_WRAP_H_

#include "overload_executor.h"
#include "value_converter_base.h"

#include "class_wrap.h"


/** 
 * @addtogroup overload_resolution
 * @{
 */


/**
 * @brief namespace wrap for wrapping namespace resolution functionality
 * The main difference between namespace and class wrappers are that classes can be instantiated
 * 
 */
class namespace_wrap {
private:
	v8::Local<v8::Object> _target;
	std::shared_ptr<overload_executor> _executor;
	const std::string _namespace;
public:
	/**
	 * @brief Construct a new namespace wrap from target object to use executor for runing callback with name ns
	 * 
	 * @param target the v8 object to add namepace wrap functionality
	 * @param executor the executor to use when calling functionality on the namespace wrap
	 * @param ns the namespace name
	 */
	namespace_wrap(v8::Local<v8::Object> target, std::shared_ptr<overload_executor> executor, const std::string &&ns);

	/**
	 * @brief adds a sub namespace
	 * 
	 * @param namespace_name the name of the sub namespace
	 * @return std::shared_ptr<namespace_wrap> an instance of namespace_wrap for the new namespace
	 */
	std::shared_ptr<namespace_wrap> add_namespace(const std::string &&namespace_name);

	/**
	 * @brief adds a class to the namespace
	 * 
	 * @param class_name the class name to add
	 * @return std::shared_ptr<class_wrap> an instance of class wrap for the new class
	 */
	std::shared_ptr<class_wrap> add_class(const std::string &&class_name);

	/**
	 * @brief adds an overload function callback
	 * 
	 * @param functionName function name to add
	 * @param arguments a list of arguments for the function
	 * @param callback POLY_METHOD callback to execute when the function is called
	 */
	void add_overload(const std::string &&functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	/**
	 * @brief adds an enum to the namespace
	 * 
	 * @param enumName name of enum
	 * @param values a list of key/value for the enum
	 */
	void add_enum(const std::string &&enumName, std::vector<std::pair<std::string, double>> values);
};


/** @}*/

#endif