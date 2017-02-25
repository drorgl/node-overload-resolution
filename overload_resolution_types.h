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

typedef const overres::FunctionCallbackInfo<v8::Value>& POLY_METHOD_ARGS_TYPE;
typedef void(*PolyFunctionCallback)(POLY_METHOD_ARGS_TYPE);

struct overload_info;

struct o_r_function {
	PolyFunctionCallback function;
	std::string functionName;
	std::string className;
	bool is_constructor;
	bool is_static;
	std::vector<std::shared_ptr<overload_info>> parameters;
};

struct o_r_class {
	std::string className;
	std::unordered_map<std::string, std::vector<std::shared_ptr< o_r_function>>> functions;
};

struct o_r_namespace {
	std::string name;
	std::unordered_map<std::string, std::shared_ptr< o_r_class>> classes;
};

#endif