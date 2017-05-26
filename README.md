# node overload resolution


Linux (multiple node versions, 6,7,latest): [![Travis CI Build Status](https://api.travis-ci.org/drorgl/node-overload-resolution.svg)](https://travis-ci.org/drorgl/node-overload-resolution)

node function call overload resolution module, in essence registering multiple function overloads and determining which overload to call based on function parameters.

# Objective

Function overloads is not part of javascript as functions are objects inside object properties and object property names are unique.

This project attempts to add overload resolution on top of node js c++ addons for easily importing c++ libraries.

Before you read on, make sure you understand [Native Abstractions for Node.js (NAN)](https://github.com/nodejs/nan)  as it relies on it for some of its functionality and builds on top of it.

# Structure 
overload_resolution - the main class that registers and calls the overloaded functions, it provides a macro POLY_METHOD which is almost identical to NAN_METHOD for declaring functions and calling them after the correct overload has been determined.

by itself, the class does nothing, you will still have to register all the callbacks to overload_resolution::execute function for it to do anything:

Declare a callback:
```c++
namespace general_callback {
	std::shared_ptr<overload_resolution> overload;
	NAN_METHOD(tester_callback) {
		return overload->execute("current_namespace", info);
	}
}
```

in the init function, populate general_callback::overload with overload resolution instance:
```c++
general_callback::overload = overload;
```
and tell v8 you want to callback into tester_callback:
```c++
Nan::SetMethod(target, "overloaded_function", general_callback::tester_callback);
```

now the hook is ready to call overload_resolution::execute whenever overloaded_function is called, but we need to tell overload_resolution which function to call when an overload is matched:

constructor:
```c++
overload->addOverloadConstructor(
			"", 
					"constructor_class_tester", 
							{ make_param("a","Number") }, 
									New_number);
			^ namespace or empty
					^ class name 
							^ array of parameter names, types and default values
							  note that Nan::Undefined is used as no default
									^ callback POLY_METHOD
```
static:
```c++
overload->addStaticOverload(
			"", 
					"constructor_class_tester", 
							"static_function", 
									{ make_param("a","String") }, 
											static_function_static_string);
			^ namespace or empty
					^ class name or function group name or empty
							^ function name
									^ array of parameter names, types and default values
											^ callback POLY_METHOD
```
member:
```c++
overload->addOverload(
			"", 
					"constructor_class_tester", 
							"member_function", 
									{ make_param("a","Map") }, 
											static_function_instance_map);
			^ namespace or empty
					^ class name
							^ function name
									^ array of parameter names, types and default values
											^ callback POLY_METHOD
```


# Wrappers
Since its inefficient to write so much code, make sure SetMethod and SetPrototypeMethod is called on each overload and track the namespaces used to store the callbacks manually, an experimental namespace_wrap and class_wrap were introduced, these two classes wrap the needed calls as well as track the targets (v8::Object).

The wrappers do add overhead to function execution time but it didn't even register when I did performance analysis.

to use the wrappers you'll need to initialize an overload overload_resolution instance normally but also start tracking a root target:
```
void init(v8::Handle<v8::Object> target) {
	auto overload = std::make_shared<overload_resolution>();
	auto base_overload = overload->register_module(target);
    ...
}
NODE_MODULE(tester, init);
```

once you have the base_overload you can start attaching methods:
```
base_overload->add_overload("standalone_function_construct", {}, standalone_function_construct);
```
nest methods:
```
auto nested = base_overload->add_namespace("namespace_construct");
nested->add_overload("nc_standalone_function_construct", {}, nc_standalone_function_construct_nc);
```
add classes:
```
auto class_def = base_overload->add_class("class_constructs");
class_def->add_overload_constructor({}, New);
class_def->add_static_overload("test_static", {}, test_static);
class_def->add_overload("test_member", {}, test_member);

constructor.Reset(class_def->done<class_constructs>());
```
note: you must call done\<T\>() when you're done defining the class methods, otherwise the class won't register in both the overload_resolution and V8.

for now classes can be nested inside namespaces but not the other way around, though it should be theoretically possible.

# Issues
Currently the project is working but inefficient, it does a lot behind the scenes to determine which overload should be called and hopefully the performance issues will be resolved in the future, the slowest actions are around structs, which are very slow, they were intended as automatic object structure recognition and overload resolution accordingly.

# Tests
Attempts were made to have as many tests as possible, at the moment of this update there are 2336 tests, all pass.

# Future
If there will be future development, it should do the following:
- performance analysis, solve the struct performance, check prototype inheritance performance and correctness, check big arrays performance.
- implement macros
- cleanup function registration
- add logging and instrumentation
- add proper v8 exceptions with more information about the failure
- add tests for function overload detection of convertible types (base/derived)


