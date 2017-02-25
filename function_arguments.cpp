#include "function_arguments.h"


namespace overres {

	function_arguments::function_arguments(type_system &typesys_, Nan::NAN_METHOD_ARGS_TYPE info_) : _typesys(typesys_), _info(info_) {
		_length = _info.Length();
		_types.resize(_length);
		_is_array.resize(_length);

		for (auto i = 0; i < _info.Length(); i++) {
			_types[i] = _typesys.determineType(_info[i]);
			_is_array[i] = _info[i]->IsArray();
		}
	}

	int& function_arguments::length() {
		return _length;
	}

	std::string function_arguments::get_type(int index) const {
		if (index >= _types.size()) {
			return "Undefined";
		}
		return _types[index];
	}

	std::string function_arguments::get_type_key() const {
		std::string key;
		for (auto i = 0; i < _length; i++) {
			if (i != 0) {
				key += ":";
			}
			key += get_type(i);
		}

		return key;
	}

	bool function_arguments::is_array(int index) {
		if (index >= _is_array.size()) {
			return _is_array[index];
		}
		return false;
	}

	bool function_arguments::is_convertible_to(int index, std::string &alias) const {
		auto param_type = get_type(index);
		auto convertible_key = param_type + ":" + alias;

		auto cached = _cache_convertible.find(convertible_key);
		if (cached != std::end(_cache_convertible)) {
			return cached->second;
		}


		auto res = _typesys.isConvertibleTo(_info[index], param_type, alias);

		if (!res) {
			res = _typesys.isArrayConvertibleTo(_info[index], param_type, alias);
		}

		_cache_convertible[convertible_key] = res;

		return res;
	}
};