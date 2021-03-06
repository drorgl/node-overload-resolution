#ifndef _TESTER_STRUCT_B_H_
#define _TESTER_STRUCT_B_H_

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_version.h>
#include <node_buffer.h>
#include <string.h>
#include <nan.h>
//#include <nan.h>

#include <memory>
#include <string>
//#include "../IStructuredObject.h"

#include "../type_system.h"

/** 
 * @addtogroup tests
 * @{
 */

/**
 * @brief example struct for struct resolution tests
 * 
 */
class struct_B : public IStructuredObject {
private:
	static std::vector<std::shared_ptr<overload_info>> _definition;

public:
	std::string prop1;
	int prop2;

	virtual bool verify(overres::type_system * ovres, v8::Local<v8::Value> obj) override;
	virtual bool parse(v8::Local<v8::Value> obj) override;

	 v8::Local<v8::Value> ToObject() override;

	 static v8::Local<v8::Object> New();
	 static v8::Local<v8::Object> New(std::string &&prop1, int prop2);
};

/** @}*/
#endif