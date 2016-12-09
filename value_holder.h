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
		virtual ~value_holder() {}
	};

	/*template<typename T>
	class value_holder : public value_holder_base {
	public:
		T* Value;
		value_holder() : value_holder_base() {}
		virtual ~value_holder() {}
	};*/
/*

	template<typename T>
	class value_holder<std::shared_ptr<T>> : public value_holder_base {
	public:
		std::shared_ptr<T> Value;
		value_holder() : value_holder_base() {}
		virtual ~value_holder() {}
	};


	template<>
	class value_holder<double> : public value_holder_base {
	public:
		double Value;
		value_holder() : value_holder_base() {}
		virtual ~value_holder() {}
	};

	template<>
	class value_holder<int> : public value_holder_base {
	public:
		int Value;
		value_holder() : value_holder_base() {}
		virtual ~value_holder() {}
	};

	template<>
	class value_holder<bool> : public value_holder_base {
	public:
		bool Value;
		value_holder() : value_holder_base() {}
		virtual ~value_holder() {}
	};

	template<>
	class value_holder<std::string> : public value_holder_base {
	public:
		std::string Value;
		value_holder() : value_holder_base() {}
		virtual ~value_holder() {}
	};*/
}

#endif