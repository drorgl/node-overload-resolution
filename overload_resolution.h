#ifndef _ALVISION_OVERLOAD_RESOLUTION_H_
#define _ALVISION_OVERLOAD_RESOLUTION_H_

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_version.h>
#include <node_buffer.h>
#include <string.h>
#include "node_modules/nan/nan.h"

#include <map>
#include <functional>

#include <set>

#include <memory>

#include <iterator>
#include <numeric>

#include "factory.h"

#include "IStructuredObject.h"

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
	const char * ns;
	const char * name;
};



struct overload_info {
	const char * parameterName;
	const char * type;
	Nan::Persistent<v8::Value, Nan::CopyablePersistentTraits<v8::Value>> defaultValue;
	overload_info(const char * parameterName, const char * type, v8::Local<v8::Value> defaultValue);
};








struct o_r_function {
	Nan::FunctionCallback function;
	const char * functionName;
	const char * className;
	std::vector<std::shared_ptr<overload_info>> parameters;
};

struct o_r_class {
	const char * className;
	std::map<std::string, std::vector<std::shared_ptr< o_r_function>>> functions;
};

struct o_r_namespace {
	const char * name;
	std::map<std::string, std::shared_ptr< o_r_class>> classes;
};
//

class IStructuredObject;

class overload_resolution {
private:
	//list of primitive types for conversion checking
	static std::set<std::string> _convertible_primitive_types; 

	//list of primitive types for type validation
	static std::set<std::string> _primitive_types;
	
	//factory for structs, used to instantiate the appropriate struct when required or generate all structs when determining type
	//TODO: improve the struct checking process, its inefficient to create all structs for each type checking (that didn't meet primitive or classes names)
	Factory<IStructuredObject> _structured_factory;
	
	//type registry
	std::map<std::string, std::shared_ptr<object_type>> _types;

	//overload_info _emptyOverloadInfo;

	//overload registry
	std::map<std::string, o_r_namespace> _namespaces;

	//new() : Affine3<T>;
	//new (affine: _matx.Matx<T>) : Affine3<T>;
	//new (data: _mat.Mat, t ? : _matx.Vec<T> /*= Vec3::all(0)*/) : Affine3<T>;
	//new (R: _matx.Matx<T>, t ? : _matx.Vec<T> /* = Vec3::all(0)*/) : Affine3<T>;
	//new (rvec: _matx.Vec<T>, t ? : _matx.Vec<T> /* = Vec3::all(0)*/) : Affine3<T>;
	//new (vals: Array<T>) : Affine3<T>;

	void get_array_types(v8::Local<v8::Value> arr, std::set<std::string> &types);


	//takes a generic type in the form of Array<Number> or Array<Array<Number> and returns the list of separate types for type validation
	void split_generic_types(std::string type, std::set<std::string> &types);
public:
	overload_resolution();

	//function should be registerType
	//should add to it all the basics, string, number, integer, boolean, array, object(?), buffer (?), function (is it possible to know the function signature?), promises(?)
	//in case of array, which type is inside it, what to do if multiple types are in the array?
	void register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const char * ns, const char * name);

	//register struct
	template <typename TDerived>
	void register_type(const char * ns, const char * name) {
		_structured_factory.register_type<TDerived>(name);
	}

	bool validate_type_registrations();

	//adds an overload function
	void addOverload(const char * ns, const char * className, const char * functionName, std::vector<std::shared_ptr<overload_info>> arguments, Nan::FunctionCallback callback);

	//determines the type of param, primitives, registered types, registered structs
	std::string determineType(v8::Local<v8::Value> param);

	//checks if param type is convertible to type
	bool isConvertibleTo(v8::Local<v8::Value> param, const char * type);

	//retrieve a list of class names up the prototype chain
	void getPrototypeChain(v8::Local<v8::Value> param, std::vector<std::string> &chain);

	//parse the registered functions, find possible matches:
	//1. by name
	//2. by passed parameters, give higher weight to passed parameters, lower weight to default parameters, even lower weight to convertible parameters
	//3. discard non-matching options
	int MatchOverload(o_r_function *func, Nan::NAN_METHOD_ARGS_TYPE info);

	void executeBestOverload(const char * ns, std::vector<std::string> & className, const char * name, Nan::NAN_METHOD_ARGS_TYPE info);
	
	//catch-all function, looks up the function in the overloads collections and executing the right one
	Nan::NAN_METHOD_RETURN_TYPE execute(const char * name_space, Nan::NAN_METHOD_ARGS_TYPE info);

	//verifies an object/map structure against a list of properties
	bool verifyObject(std::vector<std::shared_ptr<overload_info>> props, v8::Local<v8::Value> val);

	//gets a value from an object/map
	Nan::MaybeLocal<v8::Value> GetFromObject(v8::Local<v8::Value> obj, const char * key);
};

#endif