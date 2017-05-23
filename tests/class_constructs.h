#ifndef _TESTER_CLASS_CONSTRUCTS_H_
#define _TESTER_CLASS_CONSTRUCTS_H_

#include <memory>
#include <string>
#include "../overload_resolution.h"

class class_constructs : public overres::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> target, std::shared_ptr<overload_resolution> overload);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
	virtual v8::Local<v8::Function> get_constructor();
	
	static POLY_METHOD(New);

	static POLY_METHOD(test_static);
	static POLY_METHOD(test_member);

};

#endif