#ifndef _TESTER_ISTRUCTURED_OBJECT_H_
#define _TESTER_ISTRUCTURED_OBJECT_H_

#include <nan.h>

class overload_resolution;


class IStructuredObject {

public:
	virtual bool verify(overload_resolution * ovres, v8::Local<v8::Value> obj) = 0;
	virtual bool parse(v8::Local<v8::Value> obj) = 0;
	virtual v8::Local<v8::Value> ToObject() = 0;

	virtual ~IStructuredObject() {}

};


#endif