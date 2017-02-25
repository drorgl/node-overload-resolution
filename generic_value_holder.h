#ifndef _O_R_GENERIC_VALUE_HOLDER_H_
#define _O_R_GENERIC_VALUE_HOLDER_H_

#include <memory>

#include "value_converter_base.h"
#include "value_holder.h"

namespace overres {
	class generic_value_holder {


	public:
		std::shared_ptr< overres::value_converter_base> prefetcher;
		std::shared_ptr< overres::value_holder_base> value;


		generic_value_holder() {}
		generic_value_holder(std::shared_ptr< overres::value_converter_base> value_converter, std::shared_ptr< overres::value_holder_base> value_): prefetcher(value_converter), value(value_) {
		}

		void Set(std::shared_ptr< overres::value_converter_base> value_converter, std::shared_ptr< overres::value_holder_base> value_) {
			prefetcher = value_converter;
			value = value_;
		}


		v8::Local<v8::Value> Get() {
			return prefetcher->convert(value);
		}
	};

	
}

#endif