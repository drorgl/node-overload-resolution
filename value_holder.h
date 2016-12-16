#ifndef _O_R_VALUE_HOLDER_H_
#define _O_R_VALUE_HOLDER_H_

#include "v8.h"

#include "node_modules/nan/nan.h"

namespace or {


	class value_holder_base {
	public:
		value_holder_base() {}
		virtual ~value_holder_base() = default;
	};


	template<typename T>
	class value_holder : public value_holder_base {
	public:
		T Value;
		value_holder() : value_holder_base() {}
		value_holder(T val) : value_holder_base(), Value(val) {}
		virtual ~value_holder() {}
	};


}

#endif