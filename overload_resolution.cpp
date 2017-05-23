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
}

overload_resolution::~overload_resolution() {
	Log( LogLevel::DEBUG, "terminating");
	_executor.clear();
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
	//return std::make_shared<namespace_alias>(target,)
}


void overload_resolution::add_type_alias(std::string alias, std::string type) {
	assert(!alias.empty() && "alias can not be empty");
	assert(!type.empty() && "alias type can not be empty");
	Log(LogLevel::DEBUG, [&alias, &type]() {return "adding alias " + alias + " for " + type; });
	_executor.type_system.add_type_alias(alias, type);
}




bool overload_resolution::validate_type_registrations() {
	return _executor.type_system.validate_type_registrations();
}


void overload_resolution::addOverload(const std::string ns, const std::string className, const std::string name, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	Log( LogLevel::DEBUG, [&ns, &className, &name, &arguments]() {
		return "add overload " + ns + "::" + className + "::" + name + "(" + 
			tracer::join(arguments, [](const std::shared_ptr<overload_info> oi) {return oi->type + " " + oi->parameterName; },", ") 
			+ ")"; 
	});
	std::string functionName = "+" + name;

	_executor.type_system.create_function_store(ns, className, functionName);
	
	//add function to functions collection
	auto f = std::make_shared<o_r_function>();
	f->function = callback;
	f->functionName = functionName;
	f->className = className;
	f->parameters = arguments;
	f->is_constructor = false;
	f->is_static = false;
	_executor.type_system.add_overload(ns, className, functionName, f);
}

void overload_resolution::addStaticOverload(const std::string ns, const std::string className, const std::string name, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	Log( LogLevel::DEBUG, [&ns, &className, &name, &arguments]() {
		return "add static overload " + ns + "::" + className + "::" + name + "(" +
			tracer::join(arguments, [](const std::shared_ptr<overload_info> oi) {return oi->type + " " + oi->parameterName; }, ", ")
			+ ")";
	});
	std::string functionName = "-" + name;
	_executor.type_system.create_function_store(ns, className, functionName);

	//add function to functions collection
	auto f = std::make_shared<o_r_function>();
	f->function = callback;
	f->functionName = functionName;
	f->className = className;
	f->parameters = arguments;
	f->is_constructor = false;
	f->is_static = true;
	_executor.type_system.add_overload(ns, className, functionName, f);
}

void overload_resolution::addOverloadConstructor(const std::string ns, const std::string className, std::vector<std::shared_ptr<overload_info>> arguments, PolyFunctionCallback callback) {
	Log( LogLevel::DEBUG, [&ns, &className, &arguments]() {
		return "add constructor overload " + ns + "::" + className + "::" + "(" +
			tracer::join(arguments, [](const std::shared_ptr<overload_info> oi) {return oi->type + " " + oi->parameterName; }, ", ")
			+ ")";
	});
	//add ::constructor to function name, to avoid confusion if the class has classname as a function
	std::string functionName = "%" + className;
	_executor.type_system.create_function_store(ns, className, functionName);

	//add function to functions collection
	auto f = std::make_shared<o_r_function>();
	f->function = callback;
	f->functionName = functionName;
	f->className = className;
	f->parameters = arguments;
	f->is_constructor = true;
	f->is_static = false;
	_executor.type_system.add_overload(ns, className, functionName, f);
}

