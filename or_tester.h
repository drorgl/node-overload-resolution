#ifndef _O_R_TESTER_H_
#define _O_R_TESTER_H_
#include "overload_resolution.h"
using namespace v8;

namespace general_callback {
	std::shared_ptr<overload_resolution> overload;
	NAN_METHOD(tester_callback) {
		return overload->execute("or_tester",info);
	}
}

NAN_METHOD(number_testers_number) {
	info.GetReturnValue().Set(Nan::New(".number_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_string) {
	info.GetReturnValue().Set(Nan::New(".string_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_bool) {
	info.GetReturnValue().Set(Nan::New(".bool_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_date) {
	info.GetReturnValue().Set(Nan::New(".date_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_function) {
	info.GetReturnValue().Set(Nan::New(".function_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_buffer) {
	info.GetReturnValue().Set(Nan::New(".buffer_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_map) {
	info.GetReturnValue().Set(Nan::New(".map_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_set) {
	info.GetReturnValue().Set(Nan::New(".set_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_promise) {
	info.GetReturnValue().Set(Nan::New(".promise_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_proxy) {
	info.GetReturnValue().Set(Nan::New(".proxy_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_regexp) {
	info.GetReturnValue().Set(Nan::New(".regexp_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_base_class) {
	info.GetReturnValue().Set(Nan::New(".base_class_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_derived_class) {
	info.GetReturnValue().Set(Nan::New(".derived_class_testers").ToLocalChecked());
}

NAN_METHOD(number_testers_struct_A) {
	info.GetReturnValue().Set(Nan::New(".struct_A_testers").ToLocalChecked());
}

NAN_METHOD(number_testers) {
	info.GetReturnValue().Set(Nan::New(".no_parameters_testers").ToLocalChecked());
}

NAN_METHOD(structs_testers) {
	info.GetReturnValue().Set(Nan::New("structs_testers.no_parameters").ToLocalChecked());
}

NAN_METHOD(structs_testers_struct_A) {
	info.GetReturnValue().Set(Nan::New("structs_testers.struct_A").ToLocalChecked());
}

NAN_METHOD(structs_testers_struct_B) {
	info.GetReturnValue().Set(Nan::New("structs_testers.struct_B").ToLocalChecked());
}

NAN_METHOD(structs_testers_struct_A_struct_B) {
	info.GetReturnValue().Set(Nan::New("structs_testers.struct_A_struct_B").ToLocalChecked());
}

NAN_METHOD(structs_testers_struct_B_struct_A) {
	info.GetReturnValue().Set(Nan::New("structs_testers.struct_B_struct_A").ToLocalChecked());
}

NAN_METHOD(structs_testers_struct_A_struct_A) {
	info.GetReturnValue().Set(Nan::New("structs_testers.struct_A_struct_A").ToLocalChecked());
}

NAN_METHOD(structs_testers_struct_B_struct_B) {
	info.GetReturnValue().Set(Nan::New("structs_testers.struct_B_struct_B").ToLocalChecked());
}

void RegisterORTesters(Handle<Object> target , std::shared_ptr<overload_resolution> overload) {
	auto loverload = overload;
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","Number",Nan::Undefined()) }, number_testers_number);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","String",Nan::Undefined()) }, number_testers_string);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) }, number_testers_bool);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","Date",Nan::Undefined()) }, number_testers_date);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) }, number_testers_function);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) }, number_testers_buffer);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","Map",Nan::Undefined()) }, number_testers_map);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","Set",Nan::Undefined()) }, number_testers_set);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()) }, number_testers_promise);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) }, number_testers_proxy);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) }, number_testers_regexp);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()) }, number_testers_base_class);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, number_testers_derived_class);
	overload->addOverload("or_tester","", "number_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, number_testers_struct_A);
	overload->addOverload("or_tester","", "number_testers", {  }, number_testers);


	overload->addOverload("or_tester", "", "structs_testers", {}, structs_testers);
	overload->addOverload("or_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, structs_testers_struct_A);
	overload->addOverload("or_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, structs_testers_struct_B);
	overload->addOverload("or_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()),std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, structs_testers_struct_A_struct_A);
	overload->addOverload("or_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()),std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, structs_testers_struct_B_struct_B);

	overload->addOverload("or_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()),std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, structs_testers_struct_A_struct_B);
	overload->addOverload("or_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()),std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, structs_testers_struct_B_struct_A);

	general_callback::overload = overload;
	Nan::SetMethod(target, "number_testers", general_callback::tester_callback);
	Nan::SetMethod(target, "structs_testers", general_callback::tester_callback);
}

#endif