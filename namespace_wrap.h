#ifndef _O_R_OVERLOAD_RESOLUTION_NAMESPACE_WRAP_H_
#define _O_R_OVERLOAD_RESOLUTION_NAMESPACE_WRAP_H_

#include "overload_executor.h"
#include "value_converter_base.h"

#include "class_wrap.h"

class namespace_wrap {
private:
	v8::Handle<v8::Object> _target;
	overload_executor * _executor;
	std::string _namespace;
public:
	namespace_wrap(v8::Handle<v8::Object> target, overload_executor * executor, const std::string ns);

	std::shared_ptr<namespace_wrap> add_namespace(const std::string namespace_name);

	std::shared_ptr<class_wrap> add_class(const std::string class_name);

	//adds an overload function
	void add_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback);

	//adds an enum
	void add_enum(const std::string enumName, std::vector<std::pair<std::string, double>> values);
};

#endif