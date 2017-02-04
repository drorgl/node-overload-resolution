#ifndef _O_R_TYPE_SYSTEM_H_
#define _O_R_TYPE_SYSTEM_H_

#include <nan.h>

#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <memory>
#include <map>
#include <unordered_map>
#include <functional>

#include "factory.h"
#include "IStructuredObject.h"

#include "overload_resolution_types.h"



namespace or {
	class type_system {
	private:
		

		//factory for structs, used to instantiate the appropriate struct when required or generate all structs when determining type
		//TODO: improve the struct checking process, its inefficient to create all structs for each type checking (that didn't meet primitive or classes names)
		std::shared_ptr<Factory<IStructuredObject>> _structured_factory;

		//type registry
		std::unordered_map<std::string, std::shared_ptr<object_type>> _types;

		//type alias registry
		std::unordered_map<std::string, std::string> _type_aliases;

		//overload_info _emptyOverloadInfo;

		//overload registry
		std::unordered_map<std::string, std::shared_ptr<o_r_namespace>> _namespaces;

		std::unordered_map<std::string, std::string> _cached_normalization;

		void get_array_types(v8::Local<v8::Value> arr, std::set<std::string> &types);


		//takes a generic type in the form of Array<Number> or Array<Array<Number> and returns the list of separate types for type validation
		void split_generic_types(std::string type, std::set<std::string> &types);

		
		static void LogDebug(std::function<std::string()> message);
		static void LogWarn(std::function<std::string()> message);
		

	public:
		type_system();
		~type_system();



		template <typename TObjectWrap>
		void register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const std::string ns, const std::string name) {
			static_assert(std::is_base_of< or ::ObjectWrap, TObjectWrap>::value, "TObjectWrap must inherit from ObjectWrap");

			LogDebug([&ns, &name]() { return "registering type " + ns + "::" + name; });
			assert(_types.count(name) == 0 && "type name already exists");
			if (_types.count(name) != 0) {
				LogWarn([&ns, &name]() {return "register type " + ns + "::" + name + " already exists"; });
			}

			auto ot = std::make_shared< object_type>();
			ot->function_template.Reset(functionTemplate);
			ot->ns = ns;
			ot->name = name;
			ot->value_converter = std::make_shared < or ::value_converter<TObjectWrap*>>();
			_types[name] = ot;
		}

		template <typename TDerived>
		void register_type(const std::string ns, const std::string name) {
			LogDebug([&ns, &name]() {return "registering type " + ns + "::" + name; });
			_structured_factory->register_type<TDerived>(name);
		}


		void reset();

		std::string normalize_types(std::string type);
		std::string drill_type_aliases(std::string& alias);

		//add type alias
		void add_type_alias(std::string alias, std::string type);

		//list of primitive types for conversion checking
		static std::unordered_set<std::string> convertible_primitive_types;

		//list of primitive types for type validation
		static std::unordered_set<std::string> primitive_types;

		//determines the type of param, primitives, registered types, registered structs
		std::string determineType(v8::Local<v8::Value> param);

		std::shared_ptr<object_type> get_type(std::string &type);


		//checks if param type is convertible to type
		bool isConvertibleTo(v8::Local<v8::Value> param, std::string &param_type, const std::string type);

		//retrieve a list of class names up the prototype chain
		void getPrototypeChain(v8::Local<v8::Value> param, std::vector<std::string> &chain);

		//verifies an object/map structure against a list of properties
		bool verifyObject(std::vector<std::shared_ptr<overload_info>> props, v8::Local<v8::Value> val);

		//gets a value from an object/map
		static Nan::MaybeLocal<v8::Value> GetFromObject(v8::Local<v8::Value> obj, const std::string key);

		void add_overload(const std::string &ns, const std::string &className, const std::string &functionName, std::shared_ptr<o_r_function> func);

		bool validate_type_registrations();

		void create_function_store(const std::string &ns, const std::string &className, const std::string &functionName);


		void get_classes(const std::string &ns, const std::vector<std::string> &classNames, std::vector < std::shared_ptr< o_r_class>> &classes);
		void get_functions(const std::string &ns, const std::vector<std::string> &classNames, const std::string &functionName, std::vector<std::shared_ptr< o_r_function>> &implementations);
	};

};

#endif