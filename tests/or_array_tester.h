#ifndef _O_R_ARRAY_TESTER_H_
#define _O_R_ARRAY_TESTER_H_
#include "../overload_resolution.h"

/** 
 * @addtogroup tests
 * @{
 */

/**
 * @brief example code for testing correct behavior on array types resolution
 * 
 */
namespace overres_array_tester {

	namespace general_callback {
		std::shared_ptr<overload_resolution> overload;
		NAN_METHOD(tester_callback) {
			return overload->execute("or_array_tester", info);
		}
	}

	POLY_METHOD(array_testers_number) {
		info.GetReturnValue().Set(Nan::New(".number").ToLocalChecked());
	}

	
	POLY_METHOD(array_testers_array) {
		info.GetReturnValue().Set(Nan::New(".array").ToLocalChecked());
	}
POLY_METHOD(array_testers_array_number) {
	info.GetReturnValue().Set(Nan::New(".array<number>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_string) {
	info.GetReturnValue().Set(Nan::New(".array<string>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_bool) {
	info.GetReturnValue().Set(Nan::New(".array<bool>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_date) {
	info.GetReturnValue().Set(Nan::New(".array<date>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_function) {
	info.GetReturnValue().Set(Nan::New(".array<function>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_buffer) {
	info.GetReturnValue().Set(Nan::New(".array<buffer>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_map) {
	info.GetReturnValue().Set(Nan::New(".array<map>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_set) {
	info.GetReturnValue().Set(Nan::New(".array<set>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_promise) {
	info.GetReturnValue().Set(Nan::New(".array<promise>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_proxy) {
	info.GetReturnValue().Set(Nan::New(".array<proxy>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_regexp) {
	info.GetReturnValue().Set(Nan::New(".array<regexp>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_base_class) {
	info.GetReturnValue().Set(Nan::New(".array<base_class>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_derived_class) {
	info.GetReturnValue().Set(Nan::New(".array<derived_class>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_struct_A) {
	info.GetReturnValue().Set(Nan::New(".array<struct_A>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_struct_B) {
	info.GetReturnValue().Set(Nan::New(".array<struct_B>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array) {
	info.GetReturnValue().Set(Nan::New(".array<array>").ToLocalChecked());
}

POLY_METHOD(array_testers_array_array_number) {
	info.GetReturnValue().Set(Nan::New(".array<array<number>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_string) {
	info.GetReturnValue().Set(Nan::New(".array<array<string>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_bool) {
	info.GetReturnValue().Set(Nan::New(".array<array<bool>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_date) {
	info.GetReturnValue().Set(Nan::New(".array<array<date>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_function) {
	info.GetReturnValue().Set(Nan::New(".array<array<function>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_buffer) {
	info.GetReturnValue().Set(Nan::New(".array<array<buffer>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_map) {
	info.GetReturnValue().Set(Nan::New(".array<array<map>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_set) {
	info.GetReturnValue().Set(Nan::New(".array<array<set>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_promise) {
	info.GetReturnValue().Set(Nan::New(".array<array<promise>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_proxy) {
	info.GetReturnValue().Set(Nan::New(".array<array<proxy>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_regexp) {
	info.GetReturnValue().Set(Nan::New(".array<array<regexp>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_base_class) {
	info.GetReturnValue().Set(Nan::New(".array<array<base_class>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_derived_class) {
	info.GetReturnValue().Set(Nan::New(".array<array<derived_class>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_struct_A) {
	info.GetReturnValue().Set(Nan::New(".array<array<struct_A>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_struct_B) {
	info.GetReturnValue().Set(Nan::New(".array<array<struct_B>>").ToLocalChecked());
}
POLY_METHOD(array_testers_array_array_array) {
	info.GetReturnValue().Set(Nan::New(".array<array<array>>").ToLocalChecked());
}

	
POLY_METHOD(array_testers) {
	info.GetReturnValue().Set(Nan::New(".no_parameters_testers").ToLocalChecked());
}


POLY_METHOD(array_fallback_testers_array) {
	info.GetReturnValue().Set(Nan::New(".array<int>").ToLocalChecked());
}

	void RegisterORTesters(v8::Local<v8::Object> target, std::shared_ptr<overload_resolution> overload) {
		//auto loverload = overload;
		overload->addOverload("or_array_tester", "", "array_fallback_testers", { make_param("a","Array<int>") }, array_fallback_testers_array);
		Nan::SetMethod(target, "array_fallback_testers", general_callback::tester_callback, Nan::New("array_fallback_testers").ToLocalChecked());

		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array",Nan::Undefined()) }, array_testers_array);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<int>",Nan::Undefined()) }, array_testers_array_number);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<String>",Nan::Undefined()) }, array_testers_array_string);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Boolean>",Nan::Undefined()) }, array_testers_array_bool);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Date>",Nan::Undefined()) }, array_testers_array_date);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Function>",Nan::Undefined()) }, array_testers_array_function);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Buffer>",Nan::Undefined()) }, array_testers_array_buffer);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Map>",Nan::Undefined()) }, array_testers_array_map);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Set>",Nan::Undefined()) }, array_testers_array_set);
#endif
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Promise>",Nan::Undefined()) }, array_testers_array_promise);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Proxy>",Nan::Undefined()) }, array_testers_array_proxy);
#endif
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<RegExp>",Nan::Undefined()) }, array_testers_array_regexp);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<base_class>",Nan::Undefined()) }, array_testers_array_base_class);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<derived_class>",Nan::Undefined()) }, array_testers_array_derived_class);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<struct_A>",Nan::Undefined()) }, array_testers_array_struct_A);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<struct_B>",Nan::Undefined()) }, array_testers_array_struct_B);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array>",Nan::Undefined()) }, array_testers_array_array);
		
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Number>>",Nan::Undefined()) }, array_testers_array_array_number);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<String>>",Nan::Undefined()) }, array_testers_array_array_string);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Boolean>>",Nan::Undefined()) }, array_testers_array_array_bool);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Date>>",Nan::Undefined()) }, array_testers_array_array_date);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Function>>",Nan::Undefined()) }, array_testers_array_array_function);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Buffer>>",Nan::Undefined()) }, array_testers_array_array_buffer);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Map>>",Nan::Undefined()) }, array_testers_array_array_map);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Set>>",Nan::Undefined()) }, array_testers_array_array_set);
#endif
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Promise>>",Nan::Undefined()) }, array_testers_array_array_promise);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Proxy>>",Nan::Undefined()) }, array_testers_array_array_proxy);
#endif
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<RegExp>>",Nan::Undefined()) }, array_testers_array_array_regexp);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<base_class>>",Nan::Undefined()) }, array_testers_array_array_base_class);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<derived_class>>",Nan::Undefined()) }, array_testers_array_array_derived_class);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<struct_A>>",Nan::Undefined()) }, array_testers_array_array_struct_A);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<struct_B>>",Nan::Undefined()) }, array_testers_array_array_struct_B);
		overload->addOverload("or_array_tester", "", "array_testers", { make_param("a","Array<Array<Array>>",Nan::Undefined()) }, array_testers_array_array_array);

		overload->addOverload("or_array_tester", "", "array_testers", {}, array_testers);

		general_callback::overload = overload;
		Nan::SetMethod(target, "array_testers", general_callback::tester_callback, Nan::New("array_testers").ToLocalChecked());
	}

}
/** @}*/
#endif