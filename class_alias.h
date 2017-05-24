#ifndef _O_R_OVERLOAD_RESOLUTION_CLASS_ALIAS_H_
#define _O_R_OVERLOAD_RESOLUTION_CLASS_ALIAS_H_

#include "overload_executor.h"
#include "value_converter_base.h"

class class_alias {
private:
	v8::Handle<v8::Object> _target;
	overload_executor * _executor;
	std::string _class;

	Nan::FunctionCallback * _class_callback;

public:
	class_alias(v8::Handle<v8::Object> target, overload_executor * executor, const std::string class_name);

	void add_overload_constructor(std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds an overload function
	void add_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds an overload for a static function
	void add_static_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);
};

#endif