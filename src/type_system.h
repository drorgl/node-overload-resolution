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

#include "object_type.h"
#include "ObjectWrap.h"
#include "value_converter.h"
#include "overload_info.h"

namespace overres {
	/**
	 * @brief Overload Resolution Type System
	 * 
	 */
	class type_system {
	private:
		

		//TODO: improve the struct checking process, its inefficient to create all structs for each type checking (that didn't meet primitive or classes names)
		/**
		 * @brief factory for structs, used to instantiate the appropriate struct when required or generate all structs when determining type
		 * 
		 */
		std::shared_ptr<Factory<IStructuredObject>> _structured_factory;

		/**
		 * @brief type registry
		 * 
		 */
		std::unordered_map<std::string, std::shared_ptr<object_type>> _types;

		/**
		 * @brief type alias registry
		 * 
		 */
		std::unordered_map<std::string, std::string> _type_aliases;


		/**
		 * @brief overload registry
		 * 
		 */
		std::unordered_map<std::string, std::shared_ptr<o_r_namespace>> _namespaces;

		/**
		 * @brief type normalization cache
		 * 
		 */
		std::unordered_map<std::string, std::string> _cached_normalization;

		/**
		 * @brief reads the array and attempt to detect the value types
		 * 
		 * @param arr v8 array
		 * @param types a set to populate with detected types
		 */
		void get_array_types(v8::Local<v8::Value> arr, std::set<std::string> &types);


		
		
		static void LogDebug(std::function<std::string()> message);
		static void LogWarn(std::function<std::string()> message);
		

	public:
		type_system();
		~type_system();



		template <typename TObjectWrap>
		std::shared_ptr<object_type> register_type(v8::Local<v8::FunctionTemplate> functionTemplate, const std::string &ns, const std::string &name) {
			static_assert(std::is_base_of< overres::ObjectWrap, TObjectWrap>::value, "TObjectWrap must inherit from ObjectWrap");

			LogDebug([&ns, &name]() { return "registering type " + ns + "::" + name; });
			assert(_types.count(name) == 0 && "type name already exists");
			if (_types.count(name) != 0) {
				LogWarn([&ns, &name]() {return "register type " + ns + "::" + name + " already exists"; });
			}

			auto ot = std::make_shared< object_type>();
			ot->function_template.Reset(functionTemplate);
			ot->ns = ns;
			ot->name = name;
			ot->value_converter = std::make_shared < overres::value_converter<TObjectWrap*>>();
			_types[name] = ot;

			return ot;
		}

		template <typename TDerived>
		void register_type(const std::string &&ns, const std::string &&name) {
			LogDebug([&ns, &name]() {return "registering type " + ns + "::" + name; });
			_structured_factory->register_type<TDerived>(std::move(name));
		}

		/**
		 * @brief resets all collections in type system, clears cache, remove all registered types, aliases and namespaces
		 * 
		 */
		void reset();

		/**
		 * @brief normalize types and generic types by looking up the actual types from aliases 
		 * 
		 * @param type the type to normalize
		 * @return std::string the actual type
		 */
		std::string normalize_types(std::string type);

		/**
		 * @brief drill into type aliases to find the underlying type
		 * 
		 * @param alias the alias of the type to look for 
		 * @return std::string the actual type
		 */
		std::string drill_type_aliases(const std::string& alias);

		/**
		 * @brief add type alias
		 * 
		 * @param alias the type alias
		 * @param type the actual type
		 */
		void add_type_alias(std::string alias, std::string type);


		/**
		 * @brief list of primitive types for conversion checking
		 * 
		 */
		static std::unordered_set<std::string> convertible_primitive_types;

		/**
		 * @brief list of primitive types for type validation
		 * 
		 */
		static std::unordered_set<std::string> primitive_types;

		/**
		 * @brief determines the type of param, primitives, registered types, registered structs
		 * 
		 * @param param the v8 value to detect its type
		 * @return std::string the detected type name
		 */
		std::string determineType(v8::Local<v8::Value> param);

		/**
		 * @brief Get the object type for a type name
		 * 
		 * @param type the name of the type
		 * @return std::shared_ptr<object_type> the matching object type
		 */
		std::shared_ptr<object_type> get_type(std::string &&type);

		/**
		 * @brief takes a generic type in the form of Array<Number> or Array<Array<Number> and returns the list of separate types for type validation
		 * 
		 * @param type the generic type representation
		 * @param types a list of type names
		 */
		void split_generic_types(const std::string &type, std::vector<std::string> &types);


		/**
		 * @brief check array is convertible to type
		 * 
		 * @param param v8 value to check
		 * @param param_type the declared v8 value type name
		 * @param type the type to check if the array is convertible to
		 * @return true if the array is convertible to type
		 * @return false if the array cannot be converted to type
		 */
		bool isArrayConvertibleTo(v8::Local<v8::Value> param, const std::string &param_type, const std::string &type);

		/**
		 * @brief checks if param type is convertible to type
		 * 
		 * @param param v8 value to check
		 * @param param_type the declared v8 value type name
		 * @param type the type to check if the value is convertible to
		 * @return true if the value is convertible to type
		 * @return false if the value cannot be converted to type
		 */
		bool isConvertibleTo(v8::Local<v8::Value> param,const std::string &param_type, const std::string &type);

		/**
		 * @brief Get the Prototype Chain of a value for a class instance by recursively going up the chain
		 * 
		 * @param param the class instance v8 value
		 * @param chain populated by a prototype chain type names
		 */
		void getPrototypeChain(v8::Local<v8::Value> param, std::vector<std::string> &chain);

		/**
		 * @brief verifies an object/map structure against a list of properties
		 * 
		 * @param props 
		 * @param val 
		 * @return true 
		 * @return false 
		 */
		bool verifyObject(std::vector<std::shared_ptr<overload_info>> props, v8::Local<v8::Value> val);

		//gets a value from an object/map
		static Nan::MaybeLocal<v8::Value> GetFromObject(v8::Local<v8::Value> obj, const std::string &key);

		void add_overload(const std::string &ns, const std::string &className, const std::string &functionName, std::shared_ptr<o_r_function> func);

		bool validate_type_registrations();

		void create_function_store(const std::string &ns, const std::string &className, const std::string &functionName);


		void get_classes(const std::string &ns, const std::vector<std::string> &classNames, std::vector < std::shared_ptr< o_r_class>> &classes);
		void get_functions(const std::string &ns, const std::vector<std::string> &classNames, const std::string &functionName, std::vector<std::shared_ptr< o_r_function>> &implementations);


		//adds an overload function
		void addOverload(const std::string &ns, const std::string &className, const std::string &functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

		//adds an overload for a static function
		void addStaticOverload(const std::string &ns, const std::string &className, const std::string &functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

		//adds an overload constructor
		void addOverloadConstructor(const std::string &ns, const std::string &className, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);
	};

};

#endif