#ifndef _TESTER_ISTRUCTURED_OBJECT_H_
#define _TESTER_ISTRUCTURED_OBJECT_H_


#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_version.h>
#include <node_buffer.h>
#include <string.h>
#include "node_modules/nan/nan.h"

#include <memory>
#include <string>

#include "overload_resolution.h"

using namespace v8;

class overload_resolution;


class IStructuredObject {

public:
	virtual bool verify(overload_resolution * ovres, v8::Local<v8::Value> obj);
	virtual bool parse(overload_resolution * ovres, v8::Local<v8::Value> obj);
	virtual v8::Local<v8::Value> ToObject();

};


#endif