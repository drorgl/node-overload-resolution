#include "class_alias.h"

Nan::FunctionCallback * GET_CALLBACK(std::function<void(const Nan::NAN_METHOD_ARGS_TYPE)> fn) {
	return fn.target<Nan::FunctionCallback>();
}

class_alias::class_alias(v8::Handle<v8::Object> target, overload_executor * executor, const std::string class_name) {
	_target = target;
	_executor = executor;
	_class = class_name;

	_class_callback = GET_CALLBACK([&](const Nan::NAN_METHOD_ARGS_TYPE info) {_executor->execute(_class, info); });
}

void class_alias::add_overload_constructor(std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addOverloadConstructor(_class, _class, arguments, callback);
}

//adds an overload function
void class_alias::add_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addOverload(_class, _class, functionName, arguments, callback);
}

//adds an overload for a static function
void class_alias::add_static_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addStaticOverload(_class, _class, functionName, arguments, callback);
}