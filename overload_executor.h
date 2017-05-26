#ifndef _O_R_OVERLOAD_RESOLUTION_EXECUTOR_H_
#define _O_R_OVERLOAD_RESOLUTION_EXECUTOR_H_

#include <string>
#include <vector>

#include <nan.h>

#include "overload_resolution_types.h"
#include "function_arguments.h"

#include "type_system.h"
#include "function_rank_cache.h"

class overload_executor {
private:
	
	overres::function_rank_cache _function_cache;

	//parse the registered functions, find possible matches:
	//1. by name
	//2. by passed parameters, give higher weight to passed parameters, lower weight to default parameters, even lower weight to convertible parameters
	//3. discard non-matching options
	int MatchOverload(std::vector<std::string> &classNames, std::shared_ptr<o_r_function> func, overres::function_arguments &fargs);

	void execute_overload(const std::string &ns, std::vector<std::string> &classNames, const std::string &name, std::shared_ptr<o_r_function> function, Nan::NAN_METHOD_ARGS_TYPE info);


public:
	overres::type_system type_system;

	overload_executor();
	~overload_executor();

	void clear();

	void executeBestOverload(const std::string &ns, std::vector<std::string> & className, const std::string &name, Nan::NAN_METHOD_ARGS_TYPE info);

	//catch-all function, looks up the function in the overloads collections and executing the right one
	Nan::NAN_METHOD_RETURN_TYPE execute(const std::string name_space, Nan::NAN_METHOD_ARGS_TYPE info);
};

#endif