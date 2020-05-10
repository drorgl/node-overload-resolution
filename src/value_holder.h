#ifndef _O_R_VALUE_HOLDER_H_
#define _O_R_VALUE_HOLDER_H_

#include "v8.h"

#include <nan.h>

namespace overres {

	/**
	 * @brief value holder base
	 * a generic container for values
	 * 
	 */
	class value_holder_base {
	public:
		value_holder_base() {}
		virtual ~value_holder_base() = default;
	};

	/**
	 * @brief a typed value holder
	 * a container for C++ values
	 * 
	 * @tparam T 
	 */
	template<typename T>
	class value_holder : public value_holder_base {
	public:
		/**
		 * @brief the value
		 * 
		 */
		T Value;

		/**
		 * @brief Construct a new value holder
		 * 
		 */
		value_holder() : value_holder_base() {}

		/**
		 * @brief Construct a new value holder from value
		 * 
		 * @param val 
		 */
		value_holder(T val) : value_holder_base(), Value(val) {}
		virtual ~value_holder() {}
	};


}

#endif