#ifndef _O_R_GENERIC_VALUE_HOLDER_H_
#define _O_R_GENERIC_VALUE_HOLDER_H_

#include <memory>

#include "value_converter_base.h"
#include "value_holder.h"

namespace overres {
	/**
	 * @brief Generic Value Holder
	 * Can hold C++ and V8 functions that can be converted to each other, used as a container for function call arguments
	 * 
	 */
	class generic_value_holder {


	public:
		std::shared_ptr< overres::value_converter_base> prefetcher;
		std::shared_ptr< overres::value_holder_base> value;

		/**
		 * @brief Construct a new empty generic value holder
		 * 
		 */
		generic_value_holder() {}

		/**
		 * @brief Construct a new generic value holder
		 * 
		 * @param value_converter 
		 * @param value_ 
		 */
		generic_value_holder(std::shared_ptr< overres::value_converter_base> value_converter, std::shared_ptr< overres::value_holder_base> value_): prefetcher(value_converter), value(value_) {
		}

		/**
		 * @brief Sets the value
		 * 
		 * @param value_converter 
		 * @param value_ 
		 */
		void Set(std::shared_ptr< overres::value_converter_base> value_converter, std::shared_ptr< overres::value_holder_base> value_) {
			prefetcher = value_converter;
			value = value_;
		}

		/**
		 * @brief Get a v8 value
		 * @note this function should be called when the v8 callback is actually called
		 * 
		 * @return v8::Local<v8::Value> 
		 */
		v8::Local<v8::Value> Get() {
			return prefetcher->convert(value);
		}
	};

	
}

#endif