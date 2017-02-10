#ifndef _O_R_FUNCTION_ARGUMENTS_H_
#define _O_R_FUNCTION_ARGUMENTS_H_

#include <nan.h>

#include <vector>
#include <string>
#include "type_system.h"

namespace or {
	class function_arguments {
	protected:
		Nan::NAN_METHOD_ARGS_TYPE _info;
		type_system &_typesys;

		std::vector<std::string> _types;
		std::vector<bool> _is_array;

		mutable std::unordered_map<std::string, bool> _cache_convertible;

		int _length;
	public:
		function_arguments(type_system &typesys_, Nan::NAN_METHOD_ARGS_TYPE info_);

		inline v8::Local<v8::Value> operator[](int i) const { return _info[i]; }

		int& length();

		std::string get_type(int index) const;

		std::string get_type_key() const;

		bool is_array(int index);

		bool is_convertible_to(int index, std::string &alias) const;


	};
};


#endif
