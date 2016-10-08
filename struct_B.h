#ifndef _TESTER_STRUCT_B_H_
#define _TESTER_STRUCT_B_H_

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_version.h>
#include <node_buffer.h>
#include <string.h>
#include "node_modules/nan/nan.h"

#include <memory>
#include <string>
#include "IStructuredObject.h"

#include "overload_resolution.h"

using namespace v8;



class struct_B : public IStructuredObject {
private:
	static std::vector<std::shared_ptr<overload_info>> _definition;

public:
	std::string prop1;
	int prop2;

	virtual bool verify(overload_resolution * ovres, v8::Local<v8::Value> obj);
	virtual bool parse(overload_resolution * ovres, v8::Local<v8::Value> obj);

	 v8::Local<v8::Value> ToObject();
};


#endif