#ifndef _O_R_FUNCTION_RANK_CACHE_H_
#define _O_R_FUNCTION_RANK_CACHE_H_

#include <nan.h>

#include <vector>
#include <string>
#include <unordered_map>
#include <atomic>

#include "function_arguments.h"

namespace overres {
	/**
	 * @brief function rank cache
	 * 
	 */
	class function_rank_cache {
	private:

		std::unordered_map<std::string, std::weak_ptr<o_r_function>> _cache;

#ifdef DEBUG
		mutable std::atomic<long> _cache_miss = 0;
		mutable std::atomic<long> _cache_hit = 0;
#endif
		/**
		 * @brief Get the function arguments unique key
		 * the key is determined by argument types
		 * 
		 * @param fargs function arguments
		 * @return std::string the arguments key
		 */
		std::string get_function_arguments_key(const function_arguments &fargs) const;

		/**
		 * @brief Get the overload key
		 * 
		 * @param ns namespace of the overloaded function
		 * @param classNames the class names to build the key for
		 * @param name the name of the function
		 * @return std::string the key
		 */
		std::string get_overload_key(const std::string &ns,const std::vector<std::string> &classNames, const std::string &name) const;

	public:
		/**
		 * @brief resets the rank cache
		 * in debug mode, also displays statistics of cache hit/miss
		 * 
		 */
		void reset();

		/**
		 * @brief Get the function by namespace, class names, function name and argument types
		 * 
		 * @param ns the namespace of the function
		 * @param classNames  the class names of the function
		 * @param name the name of the function
		 * @param fargs the argument types of the function
		 * @return std::weak_ptr<o_r_function> a weak pointer to the function
		 */
		std::weak_ptr<o_r_function> get_function(const std::string &ns,const std::vector<std::string> &classNames, const std::string &name,const function_arguments &fargs) const;

		/**
		 * @brief stores a function in the cache for namespace, class names, function name and argument types
		 * 
		 * @param ns the namespace of the function
		 * @param classNames the class names of the function
		 * @param name the name of the function
		 * @param fargs the argument types of the function
		 * @param func the weak pointer to the function
		 */
		void cache_function(const std::string &ns, const std::vector<std::string> &classNames, const std::string &name,const function_arguments &fargs, std::weak_ptr<o_r_function> func);
	};

};

#endif