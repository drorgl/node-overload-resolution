#ifndef _TESTER_BASE_CLASS_H_
#define _TESTER_BASE_CLASS_H_

#include <memory>
#include <string>
#include "../overload_resolution.h"


/** 
 * @addtogroup tests
 * @{
 */


	/**
	 * @brief example class for testing correct behavior on class inheritance
	 * 
	 */
	class base_class : public overres::ObjectWrap {
	private:

	public:
		static void Init(v8::Local<v8::Object> target, std::shared_ptr<overload_resolution> overload);

		std::shared_ptr<std::string> _data_base;

		static Nan::Persistent<v8::FunctionTemplate> constructor;

		virtual v8::Local<v8::Function> get_constructor() override;


		static std::shared_ptr<base_class> New();

		static NAN_METHOD(New);

		static POLY_METHOD(base_function);

		static POLY_METHOD(base_function_number);
		static POLY_METHOD(base_function_string);
		static POLY_METHOD(base_function_bool);
		static POLY_METHOD(base_function_date);
		static POLY_METHOD(base_function_function);
		static POLY_METHOD(base_function_buffer);
		static POLY_METHOD(base_function_map);
		static POLY_METHOD(base_function_set);
		static POLY_METHOD(base_function_promise);
		static POLY_METHOD(base_function_proxy);
		static POLY_METHOD(base_function_regexp);
		static POLY_METHOD(base_function_base_class);
		static POLY_METHOD(base_function_derived_class);
		static POLY_METHOD(base_function_struct_A);
		static POLY_METHOD(base_function_struct_B);
		static POLY_METHOD(base_function_array);
	};

/** @}*/
#endif