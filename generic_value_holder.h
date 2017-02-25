#ifndef _O_R_GENERIC_VALUE_HOLDER_H_
#define _O_R_GENERIC_VALUE_HOLDER_H_

#include <memory>

#include "value_converter_base.h"
#include "value_holder.h"

namespace overres {

	class generic_value_holder {
		
	public:
		void Set(std::shared_ptr< overres::value_converter_base> value_converter, std::shared_ptr< overres::value_holder_base> value_) {
			prefetcher = value_converter;
			value = value_;
		}

		std::shared_ptr< overres ::value_converter_base> prefetcher;
		std::shared_ptr< overres ::value_holder_base> value;

		template<typename T>
		void Set(T returnValue) {
			//store value_converter type
			auto returnPrefetcher = std::make_shared < overres::value_converter<T>>();

			//store value inside a valueholder
			auto valueHolder = std::make_shared < overres::value_holder<T>>();
			valueHolder->Value = returnValue;

			Set(returnPrefetcher, valueHolder);
		}

		v8::Local<v8::Value> Get() {
			return prefetcher->convert(value);
		}
	};

	template<typename T>
	std::shared_ptr<generic_value_holder> make_value(T value) {
		auto gvalue = std::make_shared<generic_value_holder>();
		gvalue->Set(value);
		return gvalue;
	}
}

#endif