#ifndef _O_R_TESTER_H_
#define _O_R_TESTER_H_
#include "../overload_resolution.h"


namespace or_tester {

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
		auto loverload = overload;
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_number);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_string);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_bool);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_date);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_function);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_buffer);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_map);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_set);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_promise);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_proxy);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_regexp);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_base_class);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_derived_class);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_struct_A);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, number_testers_struct_B);
		overload->addOverload("or_tester", "", "number_testers", { std::make_shared<overload_info>("a","Array",Nan::Undefined()) }, number_testers_array);
		overload->addOverload("or_tester", "", "number_testers", {}, number_testers);

		general_callback::overload = overload;
		Nan::SetMethod(target, "number_testers", general_callback::tester_callback);
	}

}

#endif