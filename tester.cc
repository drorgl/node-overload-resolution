#include "overload_resolution.h"

using namespace v8;

#include "base_class.h"
#include "derived_class.h"

#include "struct_A.h"
#include "struct_B.h"

#include "or_tester.h"


NAN_METHOD(testfunction_no_overload_resolution) {
	info.GetReturnValue().Set(Nan::New<v8::String>("testfunction_no_overload_resolution").ToLocalChecked());
}

void init(Handle<Object> target) {
	auto overload = std::make_shared<overload_resolution>();

	overload->register_type<IStructuredObject>("", "IStructuredObject");
	overload->register_type<struct_A>("", "struct_A");
	overload->register_type<struct_B>("", "struct_B");

	Nan::SetMethod(target, "testfunction_no_overload_resolution", testfunction_no_overload_resolution);

	base_class::Init(target,overload);
	derived_class::Init(target,overload);
	RegisterORTesters(target, overload);
}

NODE_MODULE(hello, init);