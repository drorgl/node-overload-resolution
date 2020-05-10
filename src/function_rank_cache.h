#ifndef _O_R_FUNCTION_RANK_CACHE_H_
#define _O_R_FUNCTION_RANK_CACHE_H_

#include <nan.h>

#include <vector>
#include <string>
#include <unordered_map>
#include <atomic>

#include "function_arguments.h"

namespace overres {
	class function_rank_cache {
	private:
		std::unordered_map<std::string, std::weak_ptr<o_r_function>> _cache;

#ifdef DEBUG
		mutable std::atomic<long> _cache_miss = 0;
		mutable std::atomic<long> _cache_hit = 0;
#endif

		std::string get_function_arguments_key(const function_arguments &fargs) const;

		std::string get_overload_key(const std::string &ns,const std::vector<std::string> &classNames, const std::string &name) const;

	public:
		void reset();

		std::weak_ptr<o_r_function> get_function(const std::string &ns,const std::vector<std::string> &classNames, const std::string &name,const function_arguments &fargs) const;

		void cache_function(const std::string &ns, const std::vector<std::string> &classNames, const std::string &name,const function_arguments &fargs, std::weak_ptr<o_r_function> func);
	};

};

#endif