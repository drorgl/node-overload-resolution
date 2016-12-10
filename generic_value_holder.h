#ifndef _O_R_GENERIC_VALUE_HOLDER_H_
#define _O_R_GENERIC_VALUE_HOLDER_H_

#include <memory>

#include "value_converter_base.h"
#include "value_holder.h"

namespace or {

	class generic_value_holder {
	private:
		std::shared_ptr< or ::prefetcher_base> _prefetcher;
		std::shared_ptr< or ::value_holder_base> _value;
	public:
		void Set(std::shared_ptr< or ::prefetcher_base> prefetcher, std::shared_ptr< or ::value_holder_base> value) {
			_prefetcher = prefetcher;
			_value = value;
		}

		template<typename T>
		void Set(T returnValue) {
			//store prefetcher type
			auto returnPrefetcher = std::make_shared < or ::prefetcher<T>>();

			//store value inside a valueholder
			auto valueHolder = std::make_shared < or ::value_holder<T>>();
			valueHolder->Value = returnValue;

			Set(returnPrefetcher, valueHolder);
		}

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