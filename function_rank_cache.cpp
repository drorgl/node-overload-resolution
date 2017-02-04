#include "function_rank_cache.h"

namespace or {

	std::string function_rank_cache::get_function_arguments_key(const function_arguments &fargs)const  {
		return fargs.get_type_key();
	}

	std::string function_rank_cache::get_overload_key(const std::string &ns, std::vector<std::string> &classNames, const std::string &name) const {
		std::string ret = ns + "::(";
		for (auto i = 0; i < classNames.size(); i++) {
			if (i != 0) {
				ret += "|";
			}
			ret += classNames[i];
		}
		ret += ")::" + name;

		return ret;
	}


	void function_rank_cache::reset() {
#ifdef DEBUG
		std::cout << "function rank cached " << _cache.size() << " hits " << _cache_hit << " miss " << _cache_miss << std::endl;
#endif
		_cache.clear();
	}

	std::weak_ptr<o_r_function> function_rank_cache::get_function(const std::string &ns, std::vector<std::string> &classNames, const std::string &name, function_arguments &fargs) const {
		auto overload_key = get_overload_key(ns, classNames, name);
		auto function_key = get_function_arguments_key(fargs);

		auto overload_function_key = overload_key + "(" + function_key + ")";

		auto cached_function = _cache.find(overload_function_key);
		if (cached_function != std::end(_cache)) {
#ifdef DEBUG
			_cache_hit++;
#endif
			return cached_function->second;
		}

#ifdef DEBUG
		_cache_miss++;
#endif
		return std::weak_ptr<o_r_function>();;
	}

	void function_rank_cache::cache_function(const std::string &ns, std::vector<std::string> &classNames, const std::string &name, function_arguments &fargs, std::weak_ptr<o_r_function> func) {
		auto overload_key = get_overload_key(ns, classNames, name);
		auto function_key = get_function_arguments_key(fargs);

		auto overload_function_key = overload_key + "(" + function_key + ")";

		_cache[overload_function_key] = func;
	}
};