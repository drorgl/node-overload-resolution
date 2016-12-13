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

#include <map>
#include <functional>

#include <set>

#include <memory>

#include <iterator>
#include <numeric>

#include "factory.h"

#include "IStructuredObject.h"

#include "FunctionCallbackInfo.h"

#include "generic_value_holder.h"
#include "Callback.h"
#include "DateTime.h"


#include "value_holder.h"
#include "value_converter.h"




#include "ObjectWrap.h"




typedef const or::FunctionCallbackInfo<v8::Value>& POLY_METHOD_ARGS_TYPE;
#define	POLY_METHOD(name)                                                       \
		Nan::NAN_METHOD_RETURN_TYPE name(POLY_METHOD_ARGS_TYPE info)

typedef void(*PolyFunctionCallback)(POLY_METHOD_ARGS_TYPE);

////overload resolution module
//
////on constructor, register each function signature and c++ function that implements it
////supply global callback for all functions
//
////when called, get the function name callback
////parse the registered functions, find possible matches:
////1. by name
////2. by passed parameters, give higher weight to passed parameters, lower weight to default parameters, even lower weight to convertible parameters
////3. discard non-matching options
////4. sort by highest score
////5. execute
//
//
////TODO:
////1. figure out a way to check the exact parameter types passed and their convertible options
////2. figure out a way to identify exposed types, Mat or Vec for example, and their parents/convertibles/interfaces
////3. figure out a way to identify arrays of types and objects
//
////two ways to get the type
////functiontemplate->HasInstance
////name each class with className
////GetConstructorName()
//
//
////how to handle generic types? two options,
////1. register each overload as different type, for example 
////   register Matx<int> and Matx<double> as two different overloads, the problem will be with combined values as Cartesian product.
////2. register as strings where T is replacable in comparison
//
////null or undefined are considered missing values
//
////how to handle inheritance, for example, is function expects Algorithm but MinProblemSolver instance was passed.
//
//
////to distinguish between integer and double:
////int64_t ival = val->IntegerValue();
////double dval = val->NumberValue();
////
////if (ival != 0 && ival == dval) return ival;
////
////if (dval > std::numeric_limits<uint64_t>::max()
////	|| dval < std::numeric_limits<uint64_t>::min())
////	throw ML::Exception("Cannot fit " + cstr(val) + " into an integer");
//
//

struct object_type {
	Nan::Persistent<v8::FunctionTemplate, Nan::CopyablePersistentTraits<v8::FunctionTemplate>> function_template;
	std::string ns;
	std::string name;
};



struct overload_info {
	std::string parameterName;
	std::string type;
	Nan::Persistent<v8::Value, Nan::CopyablePersistentTraits<v8::Value>> defaultValue;
	std::shared_ptr<or::prefetcher_base> prefetcher;
	overload_info(const std::string parameterName, const std::string type, v8::Local<v8::Value> defaultValue = Nan::Undefined());
	overload_info(const std::string parameterName, const std::string type, int defaultValue);
	overload_info(const std::string parameterName, const std::string type, double defaultValue);
	overload_info(const std::string parameterName, const std::string type, bool defaultValue);
	overload_info(const std::string parameterName, const std::string type, std::string defaultValue);
};

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, v8::Local<v8::Value> defaultValue = Nan::Undefined()) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, bool defaultValue) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, int defaultValue) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, double defaultValue) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type, std::string defaultValue) {
	return std::make_shared<overload_info>(parameterName, type, defaultValue);
}

template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type) {
	//todo: add default value conversion
	//todo: add prefetcher to overload_info
	auto prefetcher = std::make_shared < or ::prefetcher<T>>();
	auto oi = std::make_shared<overload_info>(parameterName, type);
	oi->prefetcher = prefetcher;

	return oi;
}

template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string parameterName, const std::string type,std::shared_ptr<T> defaultValue) {
	//todo: add default value conversion
	//todo: add prefetcher to overload_info
	auto prefetcher = std::make_shared < or ::prefetcher<T>>();
	auto oi = std::make_shared<overload_info>(parameterName, type,prefetcher->convert(defaultValue));
	oi->prefetcher = prefetcher;

	return oi;
}





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
	std::map<std::string, std::vector<std::shared_ptr< o_r_function>>> functions;
};

struct o_r_namespace {
	std::string name;
	std::map<std::string, std::shared_ptr< o_r_class>> classes;
};
//
//
//struct o_r_typeinfo {
//	const std::string type_name;
//	const bool isString;
//	const bool isNumber;
//	const bool isArray;
//	const bool isBuffer;
//	const bool isDate;
//	const bool isFunction;
//	const bool isConstructorFunction;
//	const bool isMap;
//	const bool isSet;
//	const bool isNull;
//	const bool isPromise;
//	const bool isProxy;
//	const bool isRegExp;
//	const bool isNativeStruct;
//	const bool isNativeClass;
//
//
//};

class IStructuredObject;

class overload_resolution {
private:
	//list of primitive types for conversion checking
	static std::set<std::string> _convertible_primitive_types; 

	//list of primitive types for type validation
	static std::set<std::string> _primitive_types;
	
	//factory for structs, used to instantiate the appropriate struct when required or generate all structs when determining type
	//TODO: improve the struct checking process, its inefficient to create all structs for each type checking (that didn't meet primitive or classes names)
	std::shared_ptr<Factory<IStructuredObject>> _structured_factory;
	
	//type registry
	std::map<std::string, std::shared_ptr<object_type>> _types;

	//type alias registry
	std::map<std::string, std::string> _type_aliases;

	//overload_info _emptyOverloadInfo;

	//overload registry
	std::map<std::string, std::shared_ptr<o_r_namespace>> _namespaces;

	//new() : Affine3<T>;
	//new (affine: _matx.Matx<T>) : Affine3<T>;
	//new (data: _mat.Mat, t ? : _matx.Vec<T> /*= Vec3::all(0)*/) : Affine3<T>;
	//new (R: _matx.Matx<T>, t ? : _matx.Vec<T> /* = Vec3::all(0)*/) : Affine3<T>;
	//new (rvec: _matx.Vec<T>, t ? : _matx.Vec<T> /* = Vec3::all(0)*/) : Affine3<T>;
	//new (vals: Array<T>) : Affine3<T>;

	void get_array_types(v8::Local<v8::Value> arr, std::set<std::string> &types);


	//takes a generic type in the form of Array<Number> or Array<Array<Number> and returns the list of separate types for type validation
	void split_generic_types(std::string type, std::set<std::string> &types);

	void create_function_store(const std::string ns, const std::string className, const std::string functionName);

	std::string drill_type_aliases(std::string alias);

	std::string normalize_types(std::string type);
public:
	overload_resolution();

	~overload_resolution();

	//function should be registerType
	//should add to it all the basics, string, number, integer, boolean, array, object(?), buffer (?), function (is it possible to know the function signature?), promises(?)
	//in case of array, which type is inside it, what to do if multiple types are in the array?
	void register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const std::string ns, const std::string name);

	//register struct
	template <typename TDerived>
	void register_type(const std::string ns, const std::string name) {
		_structured_factory->register_type<TDerived>(name);
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

	//determines the type of param, primitives, registered types, registered structs
	std::string determineType(v8::Local<v8::Value> param);

	//checks if param type is convertible to type
	bool isConvertibleTo(v8::Local<v8::Value> param, const std::string type);

	//retrieve a list of class names up the prototype chain
	void getPrototypeChain(v8::Local<v8::Value> param, std::vector<std::string> &chain);

	//parse the registered functions, find possible matches:
	//1. by name
	//2. by passed parameters, give higher weight to passed parameters, lower weight to default parameters, even lower weight to convertible parameters
	//3. discard non-matching options
	int MatchOverload(std::shared_ptr<o_r_function> func, Nan::NAN_METHOD_ARGS_TYPE info);

	void executeBestOverload(const std::string ns, std::vector<std::string> & className, const std::string name, Nan::NAN_METHOD_ARGS_TYPE info);
	
	//catch-all function, looks up the function in the overloads collections and executing the right one
	Nan::NAN_METHOD_RETURN_TYPE execute(const std::string name_space, Nan::NAN_METHOD_ARGS_TYPE info);

	//verifies an object/map structure against a list of properties
	bool verifyObject(std::vector<std::shared_ptr<overload_info>> props, v8::Local<v8::Value> val);

	//gets a value from an object/map
	static Nan::MaybeLocal<v8::Value> GetFromObject(v8::Local<v8::Value> obj, const std::string key);
};

#endif