#ifndef _O_R_OVERLOAD_RESOLUTION_EXECUTOR_H_
#define _O_R_OVERLOAD_RESOLUTION_EXECUTOR_H_

#include <string>
#include <vector>

#include <nan.h>

#include "overload_resolution_types.h"
#include "function_arguments.h"

#include "type_system.h"
#include "function_rank_cache.h"

/**
 * @brief overload executor finds the best matching overload callback and executes it, if none found, throws an error
 * 
 */
class overload_executor {
private:
	/**
	 * @brief function rank cache, caches functions according to determined namespace, class names, function name and argument types
	 * 
	 */
	overres::function_rank_cache _function_cache;

	/**
	 * @brief parse the registered functions, find possible matches
	 * 1. by name
	 * 2. by passed parameters, give higher weight to passed parameters, lower weight to default parameters, even lower weight to convertible parameters
	 * 3. discard non-matching options
	 * 
	 * @param classNames 
	 * @param func 
	 * @param fargs 
	 * @return int 
	 */
	int MatchOverload(const std::vector<std::string> &classNames, std::shared_ptr<o_r_function> func, overres::function_arguments &fargs);

	/**
	 * @brief executes the determined overload
	 * 
	 * @param ns 
	 * @param classNames 
	 * @param name 
	 * @param function 
	 * @param info 
	 */
	void execute_overload(const std::string &ns, const std::vector<std::string> &classNames, const std::string &name, std::shared_ptr<o_r_function> function, Nan::NAN_METHOD_ARGS_TYPE info);


public:
	overres::type_system type_system;

	overload_executor();
	~overload_executor();

	void clear();

	void executeBestOverload(const std::string &&ns, const std::vector<std::string> && className, const std::string &&name, Nan::NAN_METHOD_ARGS_TYPE info);


	/**
	 * @brief catch-all function, looks up the function in the overloads collections and executing the right one
	 * 
	 * @param name_space the current namespace, this is mostly used as a simple segregation mechanism
	 * @param info the NAN method arguments
	 * @return Nan::NAN_METHOD_RETURN_TYPE NAN method return type
	 */
	Nan::NAN_METHOD_RETURN_TYPE execute(const std::string &&name_space, Nan::NAN_METHOD_ARGS_TYPE info);
};

#endif