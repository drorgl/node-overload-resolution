#ifndef _TESTER_BASE_CLASS_H_
#define _TESTER_BASE_CLASS_H_

#include <memory>
#include <string>
#include "overload_resolution.h"
using namespace v8;


	class base_class : public Nan::ObjectWrap {
	private:

	public:
		static void Init(Handle<Object> target, std::shared_ptr<overload_resolution> overload);

		std::shared_ptr<std::string> _data;

		static Nan::Persistent<FunctionTemplate> constructor;

		static NAN_METHOD(New);

		static NAN_METHOD(base_function);
	};

#endif