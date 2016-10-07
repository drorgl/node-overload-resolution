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
////https://image.slidesharecdn.com/howtowritenodejsmodule-120415103400-phpapp01/95/how-to-write-nodejs-module-78-728.jpg?cb=1334486513
////v8 type checking
////IsArray()
////IsBoolean()
////IsDate()
////IsExternal()
////IsFalse()
////IsFunction()
////IsInt32()
////IsNull()
////IsNumber()
////IsObject()
////IsString()
////IsTrue()
////IsUint32()
////IsUndefined()
//
////v8 type conversion
////bool BooleanValue()
////int32_t Int32Value()
////int64_t IntegerValue()
////double NumberValue()
////Local<Boolean> ToBoolean()
////Utf8Value / AsciiValue Local<String> ToString()
////Local<Int32> ToInt32()
////Local<Integer> ToInteger()
////Local<Number> ToNumber()
////Get/Set/Has/Delete Local<Object> ToObject()
////Local<Uint32> ToUint32()
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
class overload_resolution {
private:
	static std::set<std::string> _primitive_types; 
	Factory<IStructuredObject> _structured_factory;
	std::map<std::string, std::shared_ptr<object_type>> _types;

	//overload_info _emptyOverloadInfo;
	std::map<std::string, o_r_namespace> _namespaces;
	//new() : Affine3<T>;
	//new (affine: _matx.Matx<T>) : Affine3<T>;
	//new (data: _mat.Mat, t ? : _matx.Vec<T> /*= Vec3::all(0)*/) : Affine3<T>;
	//new (R: _matx.Matx<T>, t ? : _matx.Vec<T> /* = Vec3::all(0)*/) : Affine3<T>;
	//new (rvec: _matx.Vec<T>, t ? : _matx.Vec<T> /* = Vec3::all(0)*/) : Affine3<T>;
	//new (vals: Array<T>) : Affine3<T>;

public:
	overload_resolution();

	//function should be registerType
	//should add to it all the basics, string, number, integer, boolean, array, object(?), buffer (?), function (is it possible to know the function signature?), promises(?)
	//in case of array, which type is inside it, what to do if multiple types are in the array?
	void register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const char * ns, const char * name);

	template <typename TDerived>
	void register_type(const char * ns, const char * name) {
		_structured_factory.register_type<TDerived>(name);
	}

	void addOverload(const char * ns, const char * className, const char * functionName, std::vector<std::shared_ptr<overload_info>> arguments, Nan::FunctionCallback callback);

	const char * determineType(v8::Local<v8::Value> param);

	bool isConvertibleTo(v8::Local<v8::Value> param, const char * type);

	void getPrototypeChain(v8::Local<v8::Value> param, std::vector<std::string> &chain);

	//parse the registered functions, find possible matches:
	//1. by name
	//2. by passed parameters, give higher weight to passed parameters, lower weight to default parameters, even lower weight to convertible parameters
	//3. discard non-matching options
	int MatchOverload(o_r_function *func, Nan::NAN_METHOD_ARGS_TYPE info);

	void executeBestOverload(const char * ns, std::vector<std::string> & className, const char * name, Nan::NAN_METHOD_ARGS_TYPE info);
	
	Nan::NAN_METHOD_RETURN_TYPE execute(const char * name_space, Nan::NAN_METHOD_ARGS_TYPE info);

};

#endif