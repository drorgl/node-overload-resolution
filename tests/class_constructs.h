#ifndef _TESTER_CLASS_CONSTRUCTS_H_
#define _TESTER_CLASS_CONSTRUCTS_H_

#include <memory>
#include <string>
#include "../overload_resolution.h"

class class_constructs : public overres::ObjectWrap {
public:
	static void Init(std::shared_ptr<namespace_wrap> overload);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
	virtual v8::Local<v8::Function> get_constructor();

	std::string _test_property;


	std::map<std::string, std::string> _test_string_indexer;

	std::map<long, std::string> _test_numeric_indexer;
	
	static POLY_METHOD(New);

	static POLY_METHOD(test_static);
	static POLY_METHOD(test_member);

	static NAN_GETTER(test_property_getter);
	static NAN_SETTER(test_property_setter);

	static NAN_PROPERTY_GETTER(test_named_index_getter);
	static NAN_PROPERTY_SETTER(test_named_index_setter);

	static NAN_INDEX_GETTER(test_index_getter);
	static NAN_INDEX_SETTER(test_index_setter);

};

#endif