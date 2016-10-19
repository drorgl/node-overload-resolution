#ifndef _TESTER_BASE_CLASS_H_
#define _TESTER_BASE_CLASS_H_

#include <memory>
#include <string>
#include "../overload_resolution.h"




	class base_class : public Nan::ObjectWrap {
	private:

	public:
		static void Init(v8::Handle<v8::Object> target, std::shared_ptr<overload_resolution> overload);

		std::shared_ptr<std::string> _data;

		static Nan::Persistent<v8::FunctionTemplate> constructor;

		static v8::Local<v8::Object> New();

		static NAN_METHOD(New);

		static NAN_METHOD(base_function);

		static NAN_METHOD(base_function_number);
		static NAN_METHOD(base_function_string);
		static NAN_METHOD(base_function_bool);
		static NAN_METHOD(base_function_date);
		static NAN_METHOD(base_function_function);
		static NAN_METHOD(base_function_buffer);
		static NAN_METHOD(base_function_map);
		static NAN_METHOD(base_function_set);
		static NAN_METHOD(base_function_promise);
		static NAN_METHOD(base_function_proxy);
		static NAN_METHOD(base_function_regexp);
		static NAN_METHOD(base_function_base_class);
		static NAN_METHOD(base_function_derived_class);
		static NAN_METHOD(base_function_struct_A);
		static NAN_METHOD(base_function_struct_B);
		static NAN_METHOD(base_function_array);
	};

#endif