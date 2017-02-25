#ifndef _O_R_VALUE_CONVERTER_BASE_H_
#define _O_R_VALUE_CONVERTER_BASE_H_

#include "v8.h"

#include <nan.h>
#include <memory>

#include "value_holder.h"


namespace overres {
	class value_converter_base {
	public:
		value_converter_base() {}
		virtual ~value_converter_base() = default;

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) = 0;

		virtual v8::Local<v8::Value> convert(std::shared_ptr< value_holder_base> from) = 0;
	};
}
#endif