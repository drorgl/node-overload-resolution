#ifndef _O_R_VALUE_CONVERTER_BASE_H_
#define _O_R_VALUE_CONVERTER_BASE_H_

#include "v8.h"

#include <nan.h>
#include <memory>

#include "value_holder.h"


namespace overres {
	/**
	 * @brief Value Converter base class
	 * 
	 */
	class value_converter_base {
	public:
		value_converter_base() {}
		virtual ~value_converter_base() = default;

		/**
		 * @brief reads a v8 value and converts it to a value holder
		 * 
		 * @param val v8 value
		 * @return std::shared_ptr<value_holder_base> typed value holder casted to value_holder_base
		 */
		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) = 0;

		/**
		 * @brief converts a value holder to v8 value
		 * 
		 * @param from value holder value
		 * @return v8::Local<v8::Value> v8 value
		 */
		virtual v8::Local<v8::Value> convert(std::shared_ptr< value_holder_base> from) = 0;
	};
}
#endif