#include "derived_class.h"

#include "constructor_class_tester.h"


namespace constructor_class_tester_general_callback {
	std::shared_ptr<overload_resolution> overload;
	NAN_METHOD(overload_callback) {
		return overload->execute("", info);
	}
}

Nan::Persistent<v8::FunctionTemplate> constructor_class_tester::constructor;

void constructor_class_tester::Init(v8::Handle<v8::Object> target, std::shared_ptr<overload_resolution> overload) {
	constructor_class_tester_general_callback::overload = overload;

	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(constructor_class_tester_general_callback::overload_callback);
	constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("constructor_class_tester").ToLocalChecked());

	assert(!derived_class::constructor.IsEmpty() && "must initialize base class before derived class!");
	ctor->Inherit(Nan::New(derived_class::constructor));

	Nan::SetPrototypeMethod(ctor, "ctype", ctype_function);



	
	//Nan::SetPrototypeMethod(ctor, "base_function", constructor_class_tester_general_callback::overload_callback);
	overload->addOverloadConstructor("", "constructor_class_tester", {}, New);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Number",Nan::Undefined()) },	    New_number);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","String",Nan::Undefined()) },	    New_string);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) },	    New_bool);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Date",Nan::Undefined()) },		    New_date);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) },	    New_function);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) },	    New_buffer);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Map",Nan::Undefined()) },		    New_map);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Set",Nan::Undefined()) },		    New_set);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()) },	    New_promise);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) },		    New_proxy);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) },	    New_regexp);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()) },    New_base_class);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, New_derived_class);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) },      New_struct_A);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) },      New_struct_B);
	overload->addOverloadConstructor("", "constructor_class_tester", { std::make_shared<overload_info>("a","Array",Nan::Undefined()) },         New_array);

	//register v8 instance callback
	Nan::SetPrototypeMethod(ctor, "static_function", constructor_class_tester_general_callback::overload_callback);

	//register instance overloads
	overload->addOverload("", "constructor_class_tester", "static_function", {}, static_function_instance);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Number",Nan::Undefined()) },        static_function_instance_number);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","String",Nan::Undefined()) },        static_function_instance_string);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) },       static_function_instance_bool);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Date",Nan::Undefined()) },	        static_function_instance_date);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) },      static_function_instance_function);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) },        static_function_instance_buffer);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Map",Nan::Undefined()) },           static_function_instance_map);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Set",Nan::Undefined()) },           static_function_instance_set);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()) },       static_function_instance_promise);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) },         static_function_instance_proxy);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) },        static_function_instance_regexp);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()) },    static_function_instance_base_class);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, static_function_instance_derived_class);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) },      static_function_instance_struct_A);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) },      static_function_instance_struct_B);
	overload->addOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Array",Nan::Undefined()) },         static_function_instance_array);

	//register v8 static callback
	Nan::SetMethod(ctor, "static_function", constructor_class_tester_general_callback::overload_callback);

	//register static overloads
	overload->addStaticOverload("", "constructor_class_tester", "static_function", {}, static_function_static);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Number",Nan::Undefined()) },        static_function_static_number);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","String",Nan::Undefined()) },        static_function_static_string);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Boolean",Nan::Undefined()) },       static_function_static_bool);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Date",Nan::Undefined()) },		  static_function_static_date);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Function",Nan::Undefined()) },	  static_function_static_function);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Buffer",Nan::Undefined()) },		  static_function_static_buffer);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Map",Nan::Undefined()) },			  static_function_static_map);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Set",Nan::Undefined()) },			  static_function_static_set);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Promise",Nan::Undefined()) },		  static_function_static_promise);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Proxy",Nan::Undefined()) },		  static_function_static_proxy);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","RegExp",Nan::Undefined()) },		  static_function_static_regexp);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","base_class",Nan::Undefined()) },	  static_function_static_base_class);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","derived_class",Nan::Undefined()) }, static_function_static_derived_class);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) },      static_function_static_struct_A);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) },      static_function_static_struct_B);
	overload->addStaticOverload("", "constructor_class_tester", "static_function", { std::make_shared<overload_info>("a","Array",Nan::Undefined()) },         static_function_static_array);



	target->Set(Nan::New("constructor_class_tester").ToLocalChecked(), ctor->GetFunction());
	overload->register_type(ctor,"", "constructor_class_tester");
};

v8::Local<v8::Object> constructor_class_tester::New() {
	auto retval = Nan::NewInstance(Nan::GetFunction(Nan::New<v8::FunctionTemplate>(constructor_class_tester::constructor)).ToLocalChecked()).ToLocalChecked();

	return retval;
}

POLY_METHOD(constructor_class_tester::New) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".no_parameters";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_number) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".number";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_string) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".string";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_bool) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".bool";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_date) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".date";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_function) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".function";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_buffer) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".buffer";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_map) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".map";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_set) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".set";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_promise) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".promise";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_proxy) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".proxy";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_regexp) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".regexp";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_base_class) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".base_class";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_derived_class) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".derived_class";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_struct_A) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".struct_A";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_struct_B) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".struct_B";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

POLY_METHOD(constructor_class_tester::New_array) {

	if (!info.IsConstructCall())
		return Nan::ThrowTypeError("Cannot call constructor as function");

	constructor_class_tester *pt;

	pt = new constructor_class_tester();
	pt->_constructor_type = ".array";

	pt->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}


NAN_METHOD(constructor_class_tester::ctype_function) {
	//return the constructor types called
	constructor_class_tester * obj = Nan::ObjectWrap::Unwrap<constructor_class_tester>(info.Holder());
	info.GetReturnValue().Set(Nan::New(obj->_constructor_type).ToLocalChecked());
}



POLY_METHOD(constructor_class_tester::static_function_static) {
	info.GetReturnValue().Set(Nan::New(".static.no_params").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_number) {
	info.GetReturnValue().Set(Nan::New(".static.number").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_string) {
	info.GetReturnValue().Set(Nan::New(".static.string").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_bool) {
	info.GetReturnValue().Set(Nan::New(".static.bool").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_date) {
	info.GetReturnValue().Set(Nan::New(".static.date").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_function) {
	info.GetReturnValue().Set(Nan::New(".static.function").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_buffer) {
	info.GetReturnValue().Set(Nan::New(".static.buffer").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_map) {
	info.GetReturnValue().Set(Nan::New(".static.map").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_set) {
	info.GetReturnValue().Set(Nan::New(".static.set").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_promise) {
	info.GetReturnValue().Set(Nan::New(".static.promise").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_proxy) {
	info.GetReturnValue().Set(Nan::New(".static.proxy").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_regexp) {
	info.GetReturnValue().Set(Nan::New(".static.regexp").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_base_class) {
	info.GetReturnValue().Set(Nan::New(".static.base_class").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_derived_class) {
	info.GetReturnValue().Set(Nan::New(".static.derived_class").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_struct_A) {
	info.GetReturnValue().Set(Nan::New(".static.struct_A").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_struct_B) {
	info.GetReturnValue().Set(Nan::New(".static.struct_B").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_static_array) {
	info.GetReturnValue().Set(Nan::New(".static.array").ToLocalChecked());
}



POLY_METHOD(constructor_class_tester::static_function_instance) {
	info.GetReturnValue().Set(Nan::New(".instance.no_params").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_number) {
	info.GetReturnValue().Set(Nan::New(".instance.number").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_string) {
	info.GetReturnValue().Set(Nan::New(".instance.string").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_bool) {
	info.GetReturnValue().Set(Nan::New(".instance.bool").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_date) {
	info.GetReturnValue().Set(Nan::New(".instance.date").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_function) {
	info.GetReturnValue().Set(Nan::New(".instance.function").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_buffer) {
	info.GetReturnValue().Set(Nan::New(".instance.buffer").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_map) {
	info.GetReturnValue().Set(Nan::New(".instance.map").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_set) {
	info.GetReturnValue().Set(Nan::New(".instance.set").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_promise) {
	info.GetReturnValue().Set(Nan::New(".instance.promise").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_proxy) {
	info.GetReturnValue().Set(Nan::New(".instance.proxy").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_regexp) {
	info.GetReturnValue().Set(Nan::New(".instance.regexp").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_base_class) {
	info.GetReturnValue().Set(Nan::New(".instance.base_class").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_derived_class) {
	info.GetReturnValue().Set(Nan::New(".instance.derived_class").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_struct_A) {
	info.GetReturnValue().Set(Nan::New(".instance.struct_A").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_struct_B) {
	info.GetReturnValue().Set(Nan::New(".instance.struct_B").ToLocalChecked());
}

POLY_METHOD(constructor_class_tester::static_function_instance_array){
	info.GetReturnValue().Set(Nan::New(".instance.array").ToLocalChecked());
}