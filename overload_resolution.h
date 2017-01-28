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
#include <unordered_map>
#include <functional>

#include <set>

#include <memory>

#include <iterator>
#include <numeric>

#include "factory.h"

#include "IStructuredObject.h"



#include "generic_value_holder.h"
#include "Callback.h"
#include "DateTime.h"


#include "value_holder.h"
#include "value_converter.h"




#include "ObjectWrap.h"

#include "overload_resolution_types.h"



////overload resolution module
//
////on constructor, register each function signature and c++ function that implements it
////supply global callback for all functions
//



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

	std::unordered_map<std::string, std::string> _cached_normalization;

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

	std::string drill_type_aliases(std::string& alias);

	std::string normalize_types(std::string type);

	static void LogDebug(std::function<std::string()> message);
	static void LogWarn(std::function<std::string()> message);
public:
	overload_resolution();

	~overload_resolution();

	//function should be registerType
	//should add to it all the basics, string, number, integer, boolean, array, object(?), buffer (?), function (is it possible to know the function signature?), promises(?)
	//in case of array, which type is inside it, what to do if multiple types are in the array?
	template <typename TObjectWrap>
	void register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const std::string ns, const std::string name) {
		static_assert(std::is_base_of<or::ObjectWrap, TObjectWrap>::value, "TObjectWrap must inherit from ObjectWrap");

		LogDebug( [&ns, &name]() { return "registering type " + ns + "::" + name; });
		assert(_types.count(name) == 0 && "type name already exists");
		if (_types.count(name) != 0) {
			LogWarn( [&ns, &name]() {return "register type " + ns + "::" + name + " already exists"; });
		}

		auto ot = std::make_shared< object_type>();
		ot->function_template.Reset(functionTemplate);
		ot->ns = ns;
		ot->name = name;
		ot->value_converter = std::make_shared < or ::value_converter<TObjectWrap*>>();
		_types[name] = ot;
	}

	//register struct
	template <typename TDerived>
	void register_type(const std::string ns, const std::string name) {	
		LogDebug([&ns, &name]() {return "registering type " + ns + "::" + name; });
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
	int MatchOverload(std::vector<std::string> &classNames, std::shared_ptr<o_r_function> func, Nan::NAN_METHOD_ARGS_TYPE info);

	void executeBestOverload(const std::string ns, std::vector<std::string> & className, const std::string name, Nan::NAN_METHOD_ARGS_TYPE info);
	
	//catch-all function, looks up the function in the overloads collections and executing the right one
	Nan::NAN_METHOD_RETURN_TYPE execute(const std::string name_space, Nan::NAN_METHOD_ARGS_TYPE info);

	//verifies an object/map structure against a list of properties
	bool verifyObject(std::vector<std::shared_ptr<overload_info>> props, v8::Local<v8::Value> val);

	//gets a value from an object/map
	static Nan::MaybeLocal<v8::Value> GetFromObject(v8::Local<v8::Value> obj, const std::string key);
};

#endif