#ifndef _O_R_TESTER_H_
#define _O_R_TESTER_H_
#include "../overload_resolution.h"


namespace overres_tester {

	namespace general_callback {
		std::shared_ptr<overload_resolution> overload;
		NAN_METHOD(tester_callback) {
			return overload->execute("or_tester", info);
		}
	}

	POLY_METHOD(number_testers_number) {
		info.GetReturnValue().Set(Nan::New(".number").ToLocalChecked());
	}

	POLY_METHOD(number_testers_string) {
		info.GetReturnValue().Set(Nan::New(".string").ToLocalChecked());
	}

	POLY_METHOD(number_testers_bool) {
		info.GetReturnValue().Set(Nan::New(".bool").ToLocalChecked());
	}

	POLY_METHOD(number_testers_date) {
		info.GetReturnValue().Set(Nan::New(".date").ToLocalChecked());
	}

	POLY_METHOD(number_testers_function) {
		info.GetReturnValue().Set(Nan::New(".function").ToLocalChecked());
	}

	POLY_METHOD(number_testers_buffer) {
		info.GetReturnValue().Set(Nan::New(".buffer").ToLocalChecked());
	}

	POLY_METHOD(number_testers_map) {
		info.GetReturnValue().Set(Nan::New(".map").ToLocalChecked());
	}

	POLY_METHOD(number_testers_set) {
		info.GetReturnValue().Set(Nan::New(".set").ToLocalChecked());
	}

	POLY_METHOD(number_testers_promise) {
		info.GetReturnValue().Set(Nan::New(".promise").ToLocalChecked());
	}

	POLY_METHOD(number_testers_proxy) {
		info.GetReturnValue().Set(Nan::New(".proxy").ToLocalChecked());
	}

	POLY_METHOD(number_testers_regexp) {
		info.GetReturnValue().Set(Nan::New(".regexp").ToLocalChecked());
	}

	POLY_METHOD(number_testers_base_class) {
		info.GetReturnValue().Set(Nan::New(".base_class").ToLocalChecked());
	}

	POLY_METHOD(number_testers_derived_class) {
		info.GetReturnValue().Set(Nan::New(".derived_class").ToLocalChecked());
	}

	POLY_METHOD(number_testers_struct_A) {
		info.GetReturnValue().Set(Nan::New(".struct_A").ToLocalChecked());
	}

	POLY_METHOD(number_testers_struct_B) {
		info.GetReturnValue().Set(Nan::New(".struct_B").ToLocalChecked());
	}

	POLY_METHOD(number_testers_array) {
		info.GetReturnValue().Set(Nan::New(".array").ToLocalChecked());
	}

	POLY_METHOD(number_testers) {
		info.GetReturnValue().Set(Nan::New(".no_parameters").ToLocalChecked());
	}

	POLY_METHOD(structs_testers) {
		info.GetReturnValue().Set(Nan::New("structs_testers.no_parameters").ToLocalChecked());
	}

	POLY_METHOD(structs_testers_struct_A) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_A").ToLocalChecked());
	}

	POLY_METHOD(structs_testers_struct_B) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_B").ToLocalChecked());
	}

	POLY_METHOD(structs_testers_struct_A_struct_B) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_A_struct_B").ToLocalChecked());
	}

	POLY_METHOD(structs_testers_struct_B_struct_A) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_B_struct_A").ToLocalChecked());
	}

	POLY_METHOD(structs_testers_struct_A_struct_A) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_A_struct_A").ToLocalChecked());
	}

	POLY_METHOD(structs_testers_struct_B_struct_B) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_B_struct_B").ToLocalChecked());
	}



	void RegisterORTesters(v8::Handle<v8::Object> target, std::shared_ptr<overload_resolution> overload) {
		//auto loverload = overload;
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","int") }, number_testers_number);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","string") }, number_testers_string);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","Boolean") }, number_testers_bool);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","Date") }, number_testers_date);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","Function") }, number_testers_function);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","Buffer") }, number_testers_buffer);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","Map") }, number_testers_map);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","Set") }, number_testers_set);
#endif
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","Promise") }, number_testers_promise);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","Proxy") }, number_testers_proxy);
#endif
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","RegExp") }, number_testers_regexp);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","base_class") }, number_testers_base_class);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","derived_class") }, number_testers_derived_class);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","struct_A") }, number_testers_struct_A);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","struct_B") }, number_testers_struct_B);
		overload->addOverload("or_tester", "", "number_testers", { make_param("a","Array") }, number_testers_array);
		overload->addOverload("or_tester", "", "number_testers", {}, number_testers);

		general_callback::overload = overload;
		Nan::SetMethod(target, "number_testers", general_callback::tester_callback);
	}

}

#endif