#include "overload_resolution.h"

using namespace v8;

#include "base_class.h"
#include "derived_class.h"

#include "or_tester.h"


NAN_METHOD(testfunction_no_overload_resolution) {
	info.GetReturnValue().Set(Nan::New<v8::String>("testfunction_no_overload_resolution").ToLocalChecked());
}

void init(Handle<Object> target) {
	auto overload = std::make_shared<overload_resolution>();


	Nan::SetMethod(target, "testfunction_no_overload_resolution", testfunction_no_overload_resolution);

	base_class::Init(target,overload);
	derived_class::Init(target,overload);
	RegisterORTesters(target, overload);
}

NODE_MODULE(hello, init);