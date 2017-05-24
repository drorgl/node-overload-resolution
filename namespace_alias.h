#ifndef _O_R_OVERLOAD_RESOLUTION_NAMESPACE_ALIAS_H_
#define _O_R_OVERLOAD_RESOLUTION_NAMESPACE_ALIAS_H_

#include "overload_executor.h"
#include "value_converter_base.h"

#include "class_alias.h"

class namespace_alias {
private:
	v8::Handle<v8::Object> _target;
	overload_executor * _executor;
	std::string _namespace;

	Nan::FunctionCallback * _ns_callback;

	//void _ns_callback(const Nan::FunctionCallbackInfo<v8::Value>& val);
public:
	namespace_alias(v8::Handle<v8::Object> target, overload_executor * executor, const std::string ns);

	std::shared_ptr<namespace_alias> add_namespace(const std::string namespace_name);

	std::shared_ptr<class_alias> add_class(const std::string class_name);

	//adds an overload function
	void add_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);
};

#endif