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



#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "overload_resolution_types.h"

#include "type_system.h"
#include "function_rank_cache.h"



////overload resolution module
//
////on constructor, register each function signature and c++ function that implements it
////supply global callback for all functions
//

namespace or {
	class function_arguments;
};


class overload_resolution {
private:
	or::type_system _type_system;
	or::function_rank_cache _function_cache;
	

	//parse the registered functions, find possible matches:
	//1. by name
	//2. by passed parameters, give higher weight to passed parameters, lower weight to default parameters, even lower weight to convertible parameters
	//3. discard non-matching options
	int MatchOverload(std::vector<std::string> &classNames, std::shared_ptr<o_r_function> func, or ::function_arguments &fargs);

	static void LogDebug(std::function<std::string()> message);
	static void LogWarn(std::function<std::string()> message);


	void execute_overload(const std::string &ns, std::vector<std::string> &classNames, const std::string &name, std::shared_ptr<o_r_function> function, Nan::NAN_METHOD_ARGS_TYPE info);

public:
	overload_resolution();

	~overload_resolution();

	//function should be registerType
	//should add to it all the basics, string, number, integer, boolean, array, object(?), buffer (?), function (is it possible to know the function signature?), promises(?)
	//in case of array, which type is inside it, what to do if multiple types are in the array?
	template <typename TObjectWrap>
	void register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const std::string ns, const std::string name) {
		_type_system.register_type<TObjectWrap>(functionTemplate, ns, name);
	}

	//register struct
	template <typename TDerived>
	void register_type(const std::string ns, const std::string name) {	
		_type_system.register_type<TDerived>(ns, name);
	}

	//add type alias
	void add_type_alias(std::string alias, std::string type);

	bool validate_type_registrations();

	//adds an overload function
	void addOverload(const std::string ns, const std::string className, const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds an overload for a static function
	void addStaticOverload(const std::string ns, const std::string className, const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds an overload constructor
	void addOverloadConstructor(const std::string ns, const std::string className, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);



	

	

	void executeBestOverload(const std::string &ns, std::vector<std::string> & className, const std::string &name, Nan::NAN_METHOD_ARGS_TYPE info);
	
	//catch-all function, looks up the function in the overloads collections and executing the right one
	Nan::NAN_METHOD_RETURN_TYPE execute(const std::string name_space, Nan::NAN_METHOD_ARGS_TYPE info);

	inline std::string get_type(v8::Local<v8::Value> param) {
		return _type_system.determineType(param);
	}
};

#endif