#ifndef _O_R_FUNCTION_ARGUMENTS_H_
#define _O_R_FUNCTION_ARGUMENTS_H_

#include <nan.h>

#include <vector>
#include <string>
#include "type_system.h"

namespace overres {
	/**
	 * @brief function arguments
	 * 
	 */
	class function_arguments {
	protected:
		type_system &_typesys;

		Nan::NAN_METHOD_ARGS_TYPE _info;

		std::vector<std::string> _types;
		std::vector<bool> _is_array;

		mutable std::unordered_map<std::string, bool> _cache_convertible;

		int _length;
	public:
		/**
		 * @brief Construct a new function arguments object from NAN_METHOD call NAN_METHOD_ARGS_TYPE argument
		 * 
		 * @param typesys_ overload resolution type system
		 * @param info_ NAN_METHOD call arguments
		 */
		function_arguments(type_system &typesys_, Nan::NAN_METHOD_ARGS_TYPE info_);

		/**
		 * @brief returns argument value at index, similar to JavaScript arguments[i]
		 * 
		 * @param i index of the argument
		 * @return v8::Local<v8::Value> v8 value
		 */
		inline v8::Local<v8::Value> operator[](int i) const { return _info[i]; }

		/**
		 * @brief number of arguments
		 * 
		 * @return int& 
		 */
		int& length();

		/**
		 * @brief Get the type of the argument at index
		 * 
		 * @param index 
		 * @return std::string 
		 */
		std::string get_type(size_t index) const;

		/**
		 * @brief returns the type signature of all the arguments
		 * 
		 * @return std::string type signature
		 */
		std::string get_type_key() const;

		/**
		 * @brief checks if the argument at index is an array
		 * 
		 * @param index the index of the argument to check
		 * @return true if the argument at index is an array
		 * @return false if the argument at index is not an array
		 */
		bool is_array(size_t index);

		/**
		 * @brief checks if the argument at index is convertible to type alias
		 * 
		 * @param index the index of the argument to check
		 * @param alias the type to check if the argument at index is convertible to
		 * @return true if the type at index is convertible alias
		 * @return false false if the type at index is not convertible to alias
		 */
		bool is_convertible_to(size_t index, const std::string &alias);


	};
};


#endif
