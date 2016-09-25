#ifndef _TESTER_DERIVED_CLASS_H_
#define _TESTER_DERIVED_CLASS_H_

#include <memory>
#include <string>
#include "overload_resolution.h"
using namespace v8;



class derived_class : public Nan::ObjectWrap {
private:

public:
	static void Init(Handle<Object> target, std::shared_ptr<overload_resolution> overload);

	std::shared_ptr<std::string> _data;

	static Nan::Persistent<FunctionTemplate> constructor;

	static NAN_METHOD(New);

	static NAN_METHOD(derived_function);
};


#endif