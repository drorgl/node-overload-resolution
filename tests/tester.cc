#include "../overload_resolution.h"

#include "base_class.h"
#include "derived_class.h"

#include "struct_A.h"
#include "struct_B.h"
#include "constructor_class_tester.h"

#include "or_tester.h"
#include "or_struct_tester.h"
#include "or_two_parameters_tester.h"
#include "or_array_tester.h"
#include "or_default_tester.h"
#include "or_value_converter.h"


NAN_METHOD(testfunction_no_overload_resolution) {
	info.GetReturnValue().Set(Nan::New<v8::String>("testfunction_no_overload_resolution").ToLocalChecked());
}



void init(v8::Handle<v8::Object> target) {
	assert(false);
	auto overload = std::make_shared<overload_resolution>();

	overload->add_type_alias("int", "Number");
	overload->add_type_alias("double", "Number");
	overload->add_type_alias("float", "Number");
	overload->add_type_alias("string", "String");
	overload->add_type_alias("bool", "Boolean");

	//overload->register_type<IStructuredObject>("", "IStructuredObject");
	overload->register_type<struct_A>("", "struct_A");
	overload->register_type<struct_B>("", "struct_B");

	Nan::SetMethod(target, "testfunction_no_overload_resolution", testfunction_no_overload_resolution);

	base_class::Init(target,overload);
	derived_class::Init(target,overload);
	constructor_class_tester::Init(target, overload);
	or_tester::RegisterORTesters(target, overload);
	or_struct_tester::RegisterORTesters(target, overload);
	or_two_parameters_tester::RegisterORTesters(target, overload);
	or_array_tester::RegisterORTesters(target, overload);
	or_default_parameters_tester::RegisterORTesters(target, overload);
	or_value_converter::RegisterORTesters(target, overload);

	assert(overload->validate_type_registrations());


	//test strong type parameters
	//printf(MyClass<int>::name);
	//printf("\r\n");
	//printf(MyClass<std::vector<std::string>>::name);
	//printf("\r\n");
	//DECLARE_TYPE_NAME(std::vector<std::string>);


	//printf(gettype<std::vector<std::string>>());
	//printf("\r\n");

	//printf(typeid(std::vector<std::string>).name());
	//printf("\r\n");
	//printf(typeid(v8::Object).name());
	//printf("\r\n");


	//array<string>
	//array<int>
	//array<array<int>>
	//array<array<number>>
	//array<array<struct_A>>
	//overload->addOverload("", "derived_class", "base_function", { make_param("a","Array<Number>",Nan::Undefined()) }, base_function_number);
	//overload->addOverload("", "derived_class", "base_function", { make_param("a","Array<Array<Number>>",Nan::Undefined()) }, base_function_number);

}

NODE_MODULE(hello, init);