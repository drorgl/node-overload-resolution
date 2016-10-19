#include "../overload_resolution.h"

#include "base_class.h"
#include "derived_class.h"

#include "struct_A.h"
#include "struct_B.h"

#include "or_tester.h"
#include "or_struct_tester.h"
#include "or_two_parameters_tester.h"
#include "or_array_tester.h"
#include "or_default_tester.h"


NAN_METHOD(testfunction_no_overload_resolution) {
	info.GetReturnValue().Set(Nan::New<v8::String>("testfunction_no_overload_resolution").ToLocalChecked());
}


//strong types research
template <typename T>
class MyClass {
public:
	static const char *name; // Not private
							 // ...
};

#define DECLARE_MY_CLASS(x) template<> const char *MyClass<x>::name = #x;

DECLARE_MY_CLASS(int);
DECLARE_MY_CLASS(std::vector<std::string>);


void init(v8::Handle<v8::Object> target) {
	auto overload = std::make_shared<overload_resolution>();

	overload->register_type<IStructuredObject>("", "IStructuredObject");
	overload->register_type<struct_A>("", "struct_A");
	overload->register_type<struct_B>("", "struct_B");

	Nan::SetMethod(target, "testfunction_no_overload_resolution", testfunction_no_overload_resolution);

	base_class::Init(target,overload);
	derived_class::Init(target,overload);
	or_tester::RegisterORTesters(target, overload);
	or_struct_tester::RegisterORTesters(target, overload);
	or_two_parameters_tester::RegisterORTesters(target, overload);
	or_array_tester::RegisterORTesters(target, overload);
	or_default_parameters_tester::RegisterORTesters(target, overload);

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
	//overload->addOverload("", "derived_class", "base_function", { std::make_shared<overload_info>("a","Array<Number>",Nan::Undefined()) }, base_function_number);
	//overload->addOverload("", "derived_class", "base_function", { std::make_shared<overload_info>("a","Array<Array<Number>>",Nan::Undefined()) }, base_function_number);

}

NODE_MODULE(hello, init);