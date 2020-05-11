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


#include "namespace_constructs.h"
#include "class_constructs.h"


#include <tracer.h>

/**
 * @defgroup tests Tests and Examples
 */



NAN_METHOD(testfunction_no_overload_resolution) {
	info.GetReturnValue().Set(Nan::New<v8::String>("testfunction_no_overload_resolution").ToLocalChecked());
}

void init(v8::Local<v8::Object> target) {
	//assert(false);
	node_addon_tracer::tracer::Init(target);
	
	auto overload = std::make_shared<overload_resolution>();
	auto base_overload = overload->register_module(target);

	namespace_constructs::Init(base_overload);

	class_constructs::Init(base_overload);

	overload->add_type_alias("int", "Number");
	overload->add_type_alias("double", "Number");
	overload->add_type_alias("float", "Number");
	overload->add_type_alias("string", "String");
	overload->add_type_alias("bool", "Boolean");

	overload->register_type<struct_A>("", "struct_A");
	overload->register_type<struct_B>("", "struct_B");

	Nan::SetMethod(target, "testfunction_no_overload_resolution", testfunction_no_overload_resolution, Nan::New("testfunction_no_overload_resolution").ToLocalChecked());

	base_class::Init(target,overload);
	derived_class::Init(target,overload);
	constructor_class_tester::Init(target, overload);
	overres_tester::RegisterORTesters(target, overload);
	overres_struct_tester::RegisterORTesters(target, overload);
	overres_two_parameters_tester::RegisterORTesters(target, overload);
	overres_array_tester::RegisterORTesters(target, overload);
	overres_default_parameters_tester::RegisterORTesters(target, overload);
	overres_value_converter::RegisterORTesters(target, overload);

	assert(overload->validate_type_registrations());

}

NODE_MODULE(hello, init);