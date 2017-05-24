#include "namespace_alias.h"

#include <functional>
#include <nan.h>

// OT => Object Type
// RT => Return Type
// A ... => Arguments
template<typename OT, typename RT, typename ... A>
struct lambda_expression {
	OT _object;
	RT(OT::*_function)(A...)const;

	lambda_expression(const OT & object)
		: _object(object), _function(&decltype(_object)::operator()) {}

	RT operator() (A ... args) const {
		return (_object.*_function)(args...);
	}
};

template<typename T, typename RT, typename ... A>
struct callback_store {
	static T* func;
	static RT callback(A ... args){
		return *func(args...);
	}
};

struct callback_store1 {
	static std::vector < std::function<void(const Nan::NAN_METHOD_ARGS_TYPE)>> _functions;

	static void callback(const Nan::NAN_METHOD_ARGS_TYPE info) {

	}
};


Nan::FunctionCallback * GET_CALLBACK(std::function<void(const Nan::NAN_METHOD_ARGS_TYPE)> fn) {
	return fn.target<Nan::FunctionCallback>();
}


namespace_alias::namespace_alias(v8::Handle<v8::Object> target, overload_executor * executor, const std::string ns) {
	_target = target;
	_executor = executor;
	_namespace = ns;

	_ns_callback = GET_CALLBACK([&](const Nan::NAN_METHOD_ARGS_TYPE info) {_executor->execute(_namespace, info); });

	//lambda_expression<decltype(lambda), int, int, int>(lambda);
	//_ns_callback = &([this](const Nan::NAN_METHOD_ARGS_TYPE info) {return _executor->execute(_namespace, info); });// ::operator();

	//auto xexecutor = std::function<void(const Nan::NAN_METHOD_ARGS_TYPE)>([&](const Nan::NAN_METHOD_ARGS_TYPE info) {executor->execute(ns, info); });
	
	//typedef void * function_t(const Nan::NAN_METHOD_ARGS_TYPE info);

	//xexecutor.target
	//auto xx = xexecutor.target<Nan::FunctionCallback >();

	//_ns_callback = xx;
	//Nan::SetMethod(_target, "x", *xx);

	//auto res = lambda_expression<decltype(this), void,const Nan::NAN_METHOD_ARGS_TYPE>(xexecutor);
	//auto cs = callback_store<decltype(xexecutor), void, const Nan::NAN_METHOD_ARGS_TYPE>();
	//cs.func = &xexecutor;
	//_ns_callback = &cs.callback;
	//_ns_callback = res();

	//	std::shared_ptr<overload_resolution> overload;
	//	NAN_METHOD(overload_callback) {
	//		return overload->execute("", info);
	//	}
	//}
	//executor->execute("",)
}

//void namespace_alias::_ns_callback(const Nan::FunctionCallbackInfo<v8::Value>& val) {
//	_executor->execute(_namespace, val);
//}

std::shared_ptr<namespace_alias> namespace_alias::add_namespace(const std::string namespace_name) {
	return std::make_shared<namespace_alias>(_target, _executor, namespace_name);
}

std::shared_ptr<class_alias> namespace_alias::add_class(const std::string class_name) {
	return std::make_shared<class_alias>(_target, _executor, class_name);
}


void namespace_alias::add_overload(const std::string functionName, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	//Nan::SetMethod(_target, functionName.c_str(), std::bind(_executor->execute(_namespace)));
	//auto bb = std::bind(&namespace_alias::_ns_callback, this, std::placeholders::_1);
	_executor->type_system.addOverload(_namespace, "", functionName, arguments, callback);
	Nan::SetMethod(_target, functionName.c_str(),* _ns_callback);
}