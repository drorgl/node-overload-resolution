#include "overload_resolution.h"

#include <iterator>
#include <algorithm>

#include <cmath>


#include <tracer.h>

#include "function_arguments.h"
#include "overload_resolution_types.h"
#include "function_rank_cache.h"



#ifdef __GNUC__
#if (__cplusplus <= 201402L)
namespace std {
	template <class C>
	constexpr auto size(const C& c) -> decltype(c.size())
	{
		return c.size();
	}

	template <class T, std::size_t N>
	constexpr std::size_t size(const T(&array)[N]) noexcept
	{
		return N;
	}
}
#endif
#endif


static void Log(LogLevel level, std::string &&message) {
	if (tracer::log_level <= level) {
		tracer::Log("overload_resolution", level, std::move(message));
	}
}

static void Log(LogLevel level, std::function<std::string()> message) {
	if (tracer::log_level <= level) {
		tracer::Log("overload_resolution", level, message);
	}
}


overload_resolution::overload_resolution() {
	Log( LogLevel::DEBUG, "initializing");
	Log(LogLevel::DEBUG, []() {return "primitive types " + tracer::join(overres::type_system::primitive_types, [](const std::string &s) {return s; }, ", "); });
	Log(LogLevel::DEBUG, []() {return "convertible primitive types " + tracer::join(overres::type_system::convertible_primitive_types, [](const std::string &s) {return s; }, ", "); });
	_executor = std::make_shared<overload_executor>();
}

overload_resolution::~overload_resolution() {
	Log( LogLevel::DEBUG, "terminating");
	_executor->clear();
#ifdef DEBUG
	_CrtDumpMemoryLeaks();
#endif
}

void overload_resolution::LogDebug(std::function<std::string()> message) {
	Log(LogLevel::DEBUG, message);
}
void overload_resolution::LogWarn(std::function<std::string()> message) {
	Log(LogLevel::WARN, message);
}


std::shared_ptr<namespace_alias> overload_resolution::register_module(v8::Handle<v8::Object> target) {
	return std::make_shared<namespace_alias>(target, _executor,"");
}


void overload_resolution::add_type_alias(std::string alias, std::string type) {
	assert(!alias.empty() && "alias can not be empty");
	assert(!type.empty() && "alias type can not be empty");
	Log(LogLevel::DEBUG, [&alias, &type]() {return "adding alias " + alias + " for " + type; });
	_executor->type_system.add_type_alias(alias, type);
}




bool overload_resolution::validate_type_registrations() {
	return _executor->type_system.validate_type_registrations();
}


void overload_resolution::addOverload(const std::string ns, const std::string className, const std::string name, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addOverload(ns, className, name, arguments, callback);
}

void overload_resolution::addStaticOverload(const std::string ns, const std::string className, const std::string name, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addStaticOverload(ns, className, name, arguments, callback);
}

void overload_resolution::addOverloadConstructor(const std::string ns, const std::string className, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	_executor->type_system.addOverloadConstructor(ns, className, arguments, callback);
}

Nan::NAN_METHOD_RETURN_TYPE overload_resolution::execute(const std::string name_space, Nan::NAN_METHOD_ARGS_TYPE info) {
	return _executor->execute(name_space, info);
}