#ifndef _TESTER_CONSTRUCTOR_CLASS_H_
#define _TESTER_CONSTRUCTOR_CLASS_H_

#include <memory>
#include <string>
#include "../overload_resolution.h"



class constructor_class_tester : public or::ObjectWrap {
private:
	std::string _constructor_type;

public:
	static void Init(v8::Handle<v8::Object> target, std::shared_ptr<overload_resolution> overload);

	std::shared_ptr<std::string> _data;

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	virtual v8::Local<v8::Function> get_constructor();

	static v8::Local<v8::Object> New();

	static POLY_METHOD(New);
	static POLY_METHOD(New_number);
	static POLY_METHOD(New_string);
	static POLY_METHOD(New_bool);
	static POLY_METHOD(New_date);
	static POLY_METHOD(New_function);
	static POLY_METHOD(New_buffer);
	static POLY_METHOD(New_map);
	static POLY_METHOD(New_set);
	static POLY_METHOD(New_promise);
	static POLY_METHOD(New_proxy);
	static POLY_METHOD(New_regexp);
	static POLY_METHOD(New_base_class);
	static POLY_METHOD(New_derived_class);
	static POLY_METHOD(New_struct_A);
	static POLY_METHOD(New_struct_B);
	static POLY_METHOD(New_array);


	static NAN_METHOD(ctype_function);

	static POLY_METHOD(static_function_static);
	static POLY_METHOD(static_function_static_number);
	static POLY_METHOD(static_function_static_string);
	static POLY_METHOD(static_function_static_bool);
	static POLY_METHOD(static_function_static_date);
	static POLY_METHOD(static_function_static_function);
	static POLY_METHOD(static_function_static_buffer);
	static POLY_METHOD(static_function_static_map);
	static POLY_METHOD(static_function_static_set);
	static POLY_METHOD(static_function_static_promise);
	static POLY_METHOD(static_function_static_proxy);
	static POLY_METHOD(static_function_static_regexp);
	static POLY_METHOD(static_function_static_base_class);
	static POLY_METHOD(static_function_static_derived_class);
	static POLY_METHOD(static_function_static_struct_A);
	static POLY_METHOD(static_function_static_struct_B);
	static POLY_METHOD(static_function_static_array);



	static POLY_METHOD(static_function_instance);
	static POLY_METHOD(static_function_instance_number);
	static POLY_METHOD(static_function_instance_string);
	static POLY_METHOD(static_function_instance_bool);
	static POLY_METHOD(static_function_instance_date);
	static POLY_METHOD(static_function_instance_function);
	static POLY_METHOD(static_function_instance_buffer);
	static POLY_METHOD(static_function_instance_map);
	static POLY_METHOD(static_function_instance_set);
	static POLY_METHOD(static_function_instance_promise);
	static POLY_METHOD(static_function_instance_proxy);
	static POLY_METHOD(static_function_instance_regexp);
	static POLY_METHOD(static_function_instance_base_class);
	static POLY_METHOD(static_function_instance_derived_class);
	static POLY_METHOD(static_function_instance_struct_A);
	static POLY_METHOD(static_function_instance_struct_B);
	static POLY_METHOD(static_function_instance_array);





};


#endif