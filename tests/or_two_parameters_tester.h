#ifndef _O_R_TWO_PARAMETERS_TESTER_H_
#define _O_R_TWO_PARAMETERS_TESTER_H_
#include "../overload_resolution.h"
using namespace v8;

namespace or_two_parameters_tester {

	namespace general_callback {
		std::shared_ptr<overload_resolution> overload;
		NAN_METHOD(tester_callback) {
			return overload->execute("or_two_tester", info);
		}
	}

	NAN_METHOD(number_testers_number_number) {
		info.GetReturnValue().Set(Nan::New(".number.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_string) {
		info.GetReturnValue().Set(Nan::New(".number.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_bool) {
		info.GetReturnValue().Set(Nan::New(".number.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_date) {
		info.GetReturnValue().Set(Nan::New(".number.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_function) {
		info.GetReturnValue().Set(Nan::New(".number.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_buffer) {
		info.GetReturnValue().Set(Nan::New(".number.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_map) {
		info.GetReturnValue().Set(Nan::New(".number.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_set) {
		info.GetReturnValue().Set(Nan::New(".number.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_promise) {
		info.GetReturnValue().Set(Nan::New(".number.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_proxy) {
		info.GetReturnValue().Set(Nan::New(".number.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_regexp) {
		info.GetReturnValue().Set(Nan::New(".number.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_base_class) {
		info.GetReturnValue().Set(Nan::New(".number.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_derived_class) {
		info.GetReturnValue().Set(Nan::New(".number.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_struct_A) {
		info.GetReturnValue().Set(Nan::New(".number.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_struct_B) {
		info.GetReturnValue().Set(Nan::New(".number.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_number_array) {
		info.GetReturnValue().Set(Nan::New(".number.array").ToLocalChecked());
	}


	NAN_METHOD(number_testers_string_number) {
		info.GetReturnValue().Set(Nan::New(".string.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_string) {
		info.GetReturnValue().Set(Nan::New(".string.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_bool) {
		info.GetReturnValue().Set(Nan::New(".string.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_date) {
		info.GetReturnValue().Set(Nan::New(".string.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_function) {
		info.GetReturnValue().Set(Nan::New(".string.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_buffer) {
		info.GetReturnValue().Set(Nan::New(".string.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_map) {
		info.GetReturnValue().Set(Nan::New(".string.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_set) {
		info.GetReturnValue().Set(Nan::New(".string.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_promise) {
		info.GetReturnValue().Set(Nan::New(".string.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_proxy) {
		info.GetReturnValue().Set(Nan::New(".string.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_regexp) {
		info.GetReturnValue().Set(Nan::New(".string.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_base_class) {
		info.GetReturnValue().Set(Nan::New(".string.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_derived_class) {
		info.GetReturnValue().Set(Nan::New(".string.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_struct_A) {
		info.GetReturnValue().Set(Nan::New(".string.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_struct_B) {
		info.GetReturnValue().Set(Nan::New(".string.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_string_array) {
		info.GetReturnValue().Set(Nan::New(".string.array").ToLocalChecked());
	}





	NAN_METHOD(number_testers_bool_number) {
		info.GetReturnValue().Set(Nan::New(".bool.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_string) {
		info.GetReturnValue().Set(Nan::New(".bool.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_bool) {
		info.GetReturnValue().Set(Nan::New(".bool.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_date) {
		info.GetReturnValue().Set(Nan::New(".bool.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_function) {
		info.GetReturnValue().Set(Nan::New(".bool.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_buffer) {
		info.GetReturnValue().Set(Nan::New(".bool.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_map) {
		info.GetReturnValue().Set(Nan::New(".bool.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_set) {
		info.GetReturnValue().Set(Nan::New(".bool.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_promise) {
		info.GetReturnValue().Set(Nan::New(".bool.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_proxy) {
		info.GetReturnValue().Set(Nan::New(".bool.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_regexp) {
		info.GetReturnValue().Set(Nan::New(".bool.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_base_class) {
		info.GetReturnValue().Set(Nan::New(".bool.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_derived_class) {
		info.GetReturnValue().Set(Nan::New(".bool.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_struct_A) {
		info.GetReturnValue().Set(Nan::New(".bool.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_struct_B) {
		info.GetReturnValue().Set(Nan::New(".bool.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_bool_array) {
		info.GetReturnValue().Set(Nan::New(".bool.array").ToLocalChecked());
	}




	NAN_METHOD(number_testers_date_number) {
		info.GetReturnValue().Set(Nan::New(".date.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_string) {
		info.GetReturnValue().Set(Nan::New(".date.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_bool) {
		info.GetReturnValue().Set(Nan::New(".date.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_date) {
		info.GetReturnValue().Set(Nan::New(".date.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_function) {
		info.GetReturnValue().Set(Nan::New(".date.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_buffer) {
		info.GetReturnValue().Set(Nan::New(".date.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_map) {
		info.GetReturnValue().Set(Nan::New(".date.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_set) {
		info.GetReturnValue().Set(Nan::New(".date.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_promise) {
		info.GetReturnValue().Set(Nan::New(".date.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_proxy) {
		info.GetReturnValue().Set(Nan::New(".date.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_regexp) {
		info.GetReturnValue().Set(Nan::New(".date.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_base_class) {
		info.GetReturnValue().Set(Nan::New(".date.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_derived_class) {
		info.GetReturnValue().Set(Nan::New(".date.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_struct_A) {
		info.GetReturnValue().Set(Nan::New(".date.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_struct_B) {
		info.GetReturnValue().Set(Nan::New(".date.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_date_array) {
		info.GetReturnValue().Set(Nan::New(".date.array").ToLocalChecked());
	}







	NAN_METHOD(number_testers_function_number) {
		info.GetReturnValue().Set(Nan::New(".function.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_string) {
		info.GetReturnValue().Set(Nan::New(".function.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_bool) {
		info.GetReturnValue().Set(Nan::New(".function.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_date) {
		info.GetReturnValue().Set(Nan::New(".function.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_function) {
		info.GetReturnValue().Set(Nan::New(".function.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_buffer) {
		info.GetReturnValue().Set(Nan::New(".function.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_map) {
		info.GetReturnValue().Set(Nan::New(".function.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_set) {
		info.GetReturnValue().Set(Nan::New(".function.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_promise) {
		info.GetReturnValue().Set(Nan::New(".function.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_proxy) {
		info.GetReturnValue().Set(Nan::New(".function.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_regexp) {
		info.GetReturnValue().Set(Nan::New(".function.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_base_class) {
		info.GetReturnValue().Set(Nan::New(".function.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_derived_class) {
		info.GetReturnValue().Set(Nan::New(".function.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_struct_A) {
		info.GetReturnValue().Set(Nan::New(".function.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_struct_B) {
		info.GetReturnValue().Set(Nan::New(".function.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_function_array) {
		info.GetReturnValue().Set(Nan::New(".function.array").ToLocalChecked());
	}





	NAN_METHOD(number_testers_buffer_number) {
		info.GetReturnValue().Set(Nan::New(".buffer.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_string) {
		info.GetReturnValue().Set(Nan::New(".buffer.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_bool) {
		info.GetReturnValue().Set(Nan::New(".buffer.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_date) {
		info.GetReturnValue().Set(Nan::New(".buffer.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_function) {
		info.GetReturnValue().Set(Nan::New(".buffer.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_buffer) {
		info.GetReturnValue().Set(Nan::New(".buffer.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_map) {
		info.GetReturnValue().Set(Nan::New(".buffer.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_set) {
		info.GetReturnValue().Set(Nan::New(".buffer.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_promise) {
		info.GetReturnValue().Set(Nan::New(".buffer.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_proxy) {
		info.GetReturnValue().Set(Nan::New(".buffer.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_regexp) {
		info.GetReturnValue().Set(Nan::New(".buffer.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_base_class) {
		info.GetReturnValue().Set(Nan::New(".buffer.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_derived_class) {
		info.GetReturnValue().Set(Nan::New(".buffer.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_struct_A) {
		info.GetReturnValue().Set(Nan::New(".buffer.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_struct_B) {
		info.GetReturnValue().Set(Nan::New(".buffer.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_buffer_array) {
		info.GetReturnValue().Set(Nan::New(".buffer.array").ToLocalChecked());
	}






	NAN_METHOD(number_testers_map_number) {
		info.GetReturnValue().Set(Nan::New(".map.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_string) {
		info.GetReturnValue().Set(Nan::New(".map.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_bool) {
		info.GetReturnValue().Set(Nan::New(".map.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_date) {
		info.GetReturnValue().Set(Nan::New(".map.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_function) {
		info.GetReturnValue().Set(Nan::New(".map.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_buffer) {
		info.GetReturnValue().Set(Nan::New(".map.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_map) {
		info.GetReturnValue().Set(Nan::New(".map.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_set) {
		info.GetReturnValue().Set(Nan::New(".map.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_promise) {
		info.GetReturnValue().Set(Nan::New(".map.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_proxy) {
		info.GetReturnValue().Set(Nan::New(".map.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_regexp) {
		info.GetReturnValue().Set(Nan::New(".map.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_base_class) {
		info.GetReturnValue().Set(Nan::New(".map.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_derived_class) {
		info.GetReturnValue().Set(Nan::New(".map.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_struct_A) {
		info.GetReturnValue().Set(Nan::New(".map.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_struct_B) {
		info.GetReturnValue().Set(Nan::New(".map.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_map_array) {
		info.GetReturnValue().Set(Nan::New(".map.array").ToLocalChecked());
	}





	NAN_METHOD(number_testers_set_number) {
		info.GetReturnValue().Set(Nan::New(".set.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_string) {
		info.GetReturnValue().Set(Nan::New(".set.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_bool) {
		info.GetReturnValue().Set(Nan::New(".set.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_date) {
		info.GetReturnValue().Set(Nan::New(".set.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_function) {
		info.GetReturnValue().Set(Nan::New(".set.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_buffer) {
		info.GetReturnValue().Set(Nan::New(".set.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_map) {
		info.GetReturnValue().Set(Nan::New(".set.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_set) {
		info.GetReturnValue().Set(Nan::New(".set.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_promise) {
		info.GetReturnValue().Set(Nan::New(".set.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_proxy) {
		info.GetReturnValue().Set(Nan::New(".set.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_regexp) {
		info.GetReturnValue().Set(Nan::New(".set.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_base_class) {
		info.GetReturnValue().Set(Nan::New(".set.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_derived_class) {
		info.GetReturnValue().Set(Nan::New(".set.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_struct_A) {
		info.GetReturnValue().Set(Nan::New(".set.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_struct_B) {
		info.GetReturnValue().Set(Nan::New(".set.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_set_array) {
		info.GetReturnValue().Set(Nan::New(".set.array").ToLocalChecked());
	}





	NAN_METHOD(number_testers_promise_number) {
		info.GetReturnValue().Set(Nan::New(".promise.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_string) {
		info.GetReturnValue().Set(Nan::New(".promise.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_bool) {
		info.GetReturnValue().Set(Nan::New(".promise.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_date) {
		info.GetReturnValue().Set(Nan::New(".promise.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_function) {
		info.GetReturnValue().Set(Nan::New(".promise.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_buffer) {
		info.GetReturnValue().Set(Nan::New(".promise.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_map) {
		info.GetReturnValue().Set(Nan::New(".promise.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_set) {
		info.GetReturnValue().Set(Nan::New(".promise.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_promise) {
		info.GetReturnValue().Set(Nan::New(".promise.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_proxy) {
		info.GetReturnValue().Set(Nan::New(".promise.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_regexp) {
		info.GetReturnValue().Set(Nan::New(".promise.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_base_class) {
		info.GetReturnValue().Set(Nan::New(".promise.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_derived_class) {
		info.GetReturnValue().Set(Nan::New(".promise.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_struct_A) {
		info.GetReturnValue().Set(Nan::New(".promise.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_struct_B) {
		info.GetReturnValue().Set(Nan::New(".promise.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_promise_array) {
		info.GetReturnValue().Set(Nan::New(".promise.array").ToLocalChecked());
	}




	NAN_METHOD(number_testers_proxy_number) {
		info.GetReturnValue().Set(Nan::New(".proxy.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_string) {
		info.GetReturnValue().Set(Nan::New(".proxy.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_bool) {
		info.GetReturnValue().Set(Nan::New(".proxy.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_date) {
		info.GetReturnValue().Set(Nan::New(".proxy.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_function) {
		info.GetReturnValue().Set(Nan::New(".proxy.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_buffer) {
		info.GetReturnValue().Set(Nan::New(".proxy.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_map) {
		info.GetReturnValue().Set(Nan::New(".proxy.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_set) {
		info.GetReturnValue().Set(Nan::New(".proxy.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_promise) {
		info.GetReturnValue().Set(Nan::New(".proxy.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_proxy) {
		info.GetReturnValue().Set(Nan::New(".proxy.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_regexp) {
		info.GetReturnValue().Set(Nan::New(".proxy.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_base_class) {
		info.GetReturnValue().Set(Nan::New(".proxy.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_derived_class) {
		info.GetReturnValue().Set(Nan::New(".proxy.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_struct_A) {
		info.GetReturnValue().Set(Nan::New(".proxy.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_struct_B) {
		info.GetReturnValue().Set(Nan::New(".proxy.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_proxy_array) {
		info.GetReturnValue().Set(Nan::New(".proxy.array").ToLocalChecked());
	}




	NAN_METHOD(number_testers_regexp_number) {
		info.GetReturnValue().Set(Nan::New(".regexp.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_string) {
		info.GetReturnValue().Set(Nan::New(".regexp.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_bool) {
		info.GetReturnValue().Set(Nan::New(".regexp.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_date) {
		info.GetReturnValue().Set(Nan::New(".regexp.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_function) {
		info.GetReturnValue().Set(Nan::New(".regexp.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_buffer) {
		info.GetReturnValue().Set(Nan::New(".regexp.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_map) {
		info.GetReturnValue().Set(Nan::New(".regexp.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_set) {
		info.GetReturnValue().Set(Nan::New(".regexp.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_promise) {
		info.GetReturnValue().Set(Nan::New(".regexp.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_proxy) {
		info.GetReturnValue().Set(Nan::New(".regexp.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_regexp) {
		info.GetReturnValue().Set(Nan::New(".regexp.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_base_class) {
		info.GetReturnValue().Set(Nan::New(".regexp.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_derived_class) {
		info.GetReturnValue().Set(Nan::New(".regexp.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_struct_A) {
		info.GetReturnValue().Set(Nan::New(".regexp.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_struct_B) {
		info.GetReturnValue().Set(Nan::New(".regexp.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_regexp_array) {
		info.GetReturnValue().Set(Nan::New(".regexp.array").ToLocalChecked());
	}





	NAN_METHOD(number_testers_base_class_number) {
		info.GetReturnValue().Set(Nan::New(".base_class.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_string) {
		info.GetReturnValue().Set(Nan::New(".base_class.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_bool) {
		info.GetReturnValue().Set(Nan::New(".base_class.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_date) {
		info.GetReturnValue().Set(Nan::New(".base_class.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_function) {
		info.GetReturnValue().Set(Nan::New(".base_class.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_buffer) {
		info.GetReturnValue().Set(Nan::New(".base_class.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_map) {
		info.GetReturnValue().Set(Nan::New(".base_class.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_set) {
		info.GetReturnValue().Set(Nan::New(".base_class.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_promise) {
		info.GetReturnValue().Set(Nan::New(".base_class.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_proxy) {
		info.GetReturnValue().Set(Nan::New(".base_class.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_regexp) {
		info.GetReturnValue().Set(Nan::New(".base_class.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_base_class) {
		info.GetReturnValue().Set(Nan::New(".base_class.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_derived_class) {
		info.GetReturnValue().Set(Nan::New(".base_class.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_struct_A) {
		info.GetReturnValue().Set(Nan::New(".base_class.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_struct_B) {
		info.GetReturnValue().Set(Nan::New(".base_class.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_base_class_array) {
		info.GetReturnValue().Set(Nan::New(".base_class.array").ToLocalChecked());
	}





	NAN_METHOD(number_testers_derived_class_number) {
		info.GetReturnValue().Set(Nan::New(".derived_class.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_string) {
		info.GetReturnValue().Set(Nan::New(".derived_class.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_bool) {
		info.GetReturnValue().Set(Nan::New(".derived_class.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_date) {
		info.GetReturnValue().Set(Nan::New(".derived_class.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_function) {
		info.GetReturnValue().Set(Nan::New(".derived_class.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_buffer) {
		info.GetReturnValue().Set(Nan::New(".derived_class.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_map) {
		info.GetReturnValue().Set(Nan::New(".derived_class.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_set) {
		info.GetReturnValue().Set(Nan::New(".derived_class.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_promise) {
		info.GetReturnValue().Set(Nan::New(".derived_class.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_proxy) {
		info.GetReturnValue().Set(Nan::New(".derived_class.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_regexp) {
		info.GetReturnValue().Set(Nan::New(".derived_class.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_base_class) {
		info.GetReturnValue().Set(Nan::New(".derived_class.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_derived_class) {
		info.GetReturnValue().Set(Nan::New(".derived_class.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_struct_A) {
		info.GetReturnValue().Set(Nan::New(".derived_class.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_struct_B) {
		info.GetReturnValue().Set(Nan::New(".derived_class.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_derived_class_array) {
		info.GetReturnValue().Set(Nan::New(".derived_class.array").ToLocalChecked());
	}




	NAN_METHOD(number_testers_struct_A_number) {
		info.GetReturnValue().Set(Nan::New(".struct_A.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_string) {
		info.GetReturnValue().Set(Nan::New(".struct_A.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_bool) {
		info.GetReturnValue().Set(Nan::New(".struct_A.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_date) {
		info.GetReturnValue().Set(Nan::New(".struct_A.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_function) {
		info.GetReturnValue().Set(Nan::New(".struct_A.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_buffer) {
		info.GetReturnValue().Set(Nan::New(".struct_A.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_map) {
		info.GetReturnValue().Set(Nan::New(".struct_A.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_set) {
		info.GetReturnValue().Set(Nan::New(".struct_A.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_promise) {
		info.GetReturnValue().Set(Nan::New(".struct_A.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_proxy) {
		info.GetReturnValue().Set(Nan::New(".struct_A.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_regexp) {
		info.GetReturnValue().Set(Nan::New(".struct_A.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_base_class) {
		info.GetReturnValue().Set(Nan::New(".struct_A.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_derived_class) {
		info.GetReturnValue().Set(Nan::New(".struct_A.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_struct_A) {
		info.GetReturnValue().Set(Nan::New(".struct_A.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_struct_B) {
		info.GetReturnValue().Set(Nan::New(".struct_A.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_A_array) {
		info.GetReturnValue().Set(Nan::New(".struct_A.array").ToLocalChecked());
	}





	NAN_METHOD(number_testers_struct_B_number) {
		info.GetReturnValue().Set(Nan::New(".struct_B.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_string) {
		info.GetReturnValue().Set(Nan::New(".struct_B.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_bool) {
		info.GetReturnValue().Set(Nan::New(".struct_B.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_date) {
		info.GetReturnValue().Set(Nan::New(".struct_B.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_function) {
		info.GetReturnValue().Set(Nan::New(".struct_B.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_buffer) {
		info.GetReturnValue().Set(Nan::New(".struct_B.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_map) {
		info.GetReturnValue().Set(Nan::New(".struct_B.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_set) {
		info.GetReturnValue().Set(Nan::New(".struct_B.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_promise) {
		info.GetReturnValue().Set(Nan::New(".struct_B.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_proxy) {
		info.GetReturnValue().Set(Nan::New(".struct_B.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_regexp) {
		info.GetReturnValue().Set(Nan::New(".struct_B.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_base_class) {
		info.GetReturnValue().Set(Nan::New(".struct_B.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_derived_class) {
		info.GetReturnValue().Set(Nan::New(".struct_B.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_struct_A) {
		info.GetReturnValue().Set(Nan::New(".struct_B.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_struct_B) {
		info.GetReturnValue().Set(Nan::New(".struct_B.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_struct_B_array) {
		info.GetReturnValue().Set(Nan::New(".struct_B.array").ToLocalChecked());
	}



	NAN_METHOD(number_testers_array_number) {
		info.GetReturnValue().Set(Nan::New(".array.number").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_string) {
		info.GetReturnValue().Set(Nan::New(".array.string").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_bool) {
		info.GetReturnValue().Set(Nan::New(".array.bool").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_date) {
		info.GetReturnValue().Set(Nan::New(".array.date").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_function) {
		info.GetReturnValue().Set(Nan::New(".array.function").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_buffer) {
		info.GetReturnValue().Set(Nan::New(".array.buffer").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_map) {
		info.GetReturnValue().Set(Nan::New(".array.map").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_set) {
		info.GetReturnValue().Set(Nan::New(".array.set").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_promise) {
		info.GetReturnValue().Set(Nan::New(".array.promise").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_proxy) {
		info.GetReturnValue().Set(Nan::New(".array.proxy").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_regexp) {
		info.GetReturnValue().Set(Nan::New(".array.regexp").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_base_class) {
		info.GetReturnValue().Set(Nan::New(".array.base_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_derived_class) {
		info.GetReturnValue().Set(Nan::New(".array.derived_class").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_struct_A) {
		info.GetReturnValue().Set(Nan::New(".array.struct_A").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_struct_B) {
		info.GetReturnValue().Set(Nan::New(".array.struct_B").ToLocalChecked());
	}
	NAN_METHOD(number_testers_array_array) {
		info.GetReturnValue().Set(Nan::New(".array.array").ToLocalChecked());
	}



	NAN_METHOD(number_testers) {
		info.GetReturnValue().Set(Nan::New(".no_params").ToLocalChecked());
	}



	void RegisterORTesters(Handle<Object> target, std::shared_ptr<overload_resolution> overload) {
		auto loverload = overload;
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_number_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_number_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_number_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_number_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_number_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_number_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_number_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_number_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_number_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_number_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_number_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_number_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_number_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_number_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_number_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_number_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_string_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_string_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_string_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_string_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_string_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_string_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_string_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_string_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_string_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_string_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_string_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_string_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_string_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_string_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_string_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_string_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_bool_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_bool_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_bool_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_bool_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_bool_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_bool_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_bool_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_bool_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_bool_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_bool_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_bool_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_bool_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_bool_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_bool_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_bool_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_bool_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_date_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_date_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_date_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_date_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_date_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_date_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_date_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_date_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_date_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_date_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_date_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_date_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_date_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_date_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_date_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_date_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_function_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_function_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_function_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_function_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_function_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_function_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_function_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_function_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_function_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_function_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_function_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_function_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_function_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_function_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) , std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_function_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_function_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_buffer_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_buffer_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_buffer_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_buffer_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_buffer_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_buffer_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_buffer_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_buffer_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_buffer_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_buffer_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_buffer_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_buffer_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_buffer_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_buffer_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_buffer_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_buffer_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_map_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_map_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_map_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_map_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_map_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_map_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_map_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_map_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_map_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_map_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_map_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_map_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_map_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_map_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_map_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_map_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_set_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_set_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_set_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_set_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_set_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_set_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_set_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_set_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_set_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_set_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_set_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_set_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_set_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_set_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_set_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_set_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_promise_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_promise_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_promise_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_promise_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_promise_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_promise_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_promise_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_promise_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_promise_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_promise_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_promise_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_promise_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_promise_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_promise_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_promise_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_promise_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_proxy_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_proxy_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_proxy_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_proxy_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_proxy_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_proxy_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_proxy_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_proxy_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_proxy_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_proxy_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_proxy_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_proxy_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_proxy_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_proxy_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_proxy_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_proxy_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_regexp_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_regexp_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_regexp_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_regexp_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_regexp_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_regexp_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_regexp_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_regexp_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_regexp_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_regexp_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_regexp_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_regexp_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_regexp_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_regexp_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_regexp_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_regexp_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_base_class_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_base_class_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_base_class_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_base_class_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_base_class_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_base_class_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_base_class_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_base_class_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_base_class_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_base_class_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_base_class_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_base_class_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_base_class_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_base_class_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_base_class_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_base_class_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_derived_class_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_derived_class_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_derived_class_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_derived_class_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_derived_class_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_derived_class_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_derived_class_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_derived_class_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_derived_class_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_derived_class_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_derived_class_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_derived_class_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_derived_class_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_derived_class_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_derived_class_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_derived_class_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_struct_A_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_struct_A_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_struct_A_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_struct_A_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_struct_A_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_struct_A_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_struct_A_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_struct_A_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_struct_A_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_struct_A_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_struct_A_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_struct_A_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_struct_A_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_struct_A_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_struct_A_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()),std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_struct_A_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_struct_B_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_struct_B_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_struct_B_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_struct_B_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_struct_B_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_struct_B_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_struct_B_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_struct_B_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_struct_B_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_struct_B_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_struct_B_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_struct_B_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_struct_B_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_struct_B_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_struct_B_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()), std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_struct_B_array);

		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_array_number);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_array_string);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_array_bool);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_array_date);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_array_function);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_array_buffer);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_array_map);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_array_set);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_array_promise);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_array_proxy);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_array_regexp);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_array_base_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_array_derived_class);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_array_struct_A);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_array_struct_B);
		overload->addOverload("or_two_tester", "", "two_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()), std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_array_array);



		overload->addOverload("or_two_tester", "", "two_testers", {}, number_testers);

		general_callback::overload = overload;
		Nan::SetMethod(target, "two_testers", general_callback::tester_callback);
	}

}

#endif