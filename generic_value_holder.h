#ifndef _O_R_GENERIC_VALUE_HOLDER_H_
#define _O_R_GENERIC_VALUE_HOLDER_H_

#include <memory>

#include "value_converter_base.h"
#include "value_holder.h"

namespace or {

	class generic_value_holder {
	private:
		std::shared_ptr< or ::value_converter_base> _prefetcher;
		std::shared_ptr< or ::value_holder_base> _value;
	public:
		void Set(std::shared_ptr< or ::value_converter_base> value_converter, std::shared_ptr< or ::value_holder_base> value) {
			_prefetcher = value_converter;
			_value = value;
		}

		template<typename T>
		void Set(T returnValue) {
			//store value_converter type
			auto returnPrefetcher = std::make_shared < or ::value_converter<T>>();

			//store value inside a valueholder
			auto valueHolder = std::make_shared < or ::value_holder<T>>();
			valueHolder->Value = returnValue;

			Set(returnPrefetcher, valueHolder);
		}

		//template<typename T>
		//std::shared_ptr<T> GetValueHolder() {
		//	return std::dynamic_pointer_cast<or ::value_holder<T>>(_value);
		//}

		v8::Local<v8::Value> Get() {
			return _prefetcher->convert(_value);
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