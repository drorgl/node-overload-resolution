# node overload resolution

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
							{ make_param("a","Number",Nan::Undefined()) }, 
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
									{ make_param("a","String",Nan::Undefined()) }, 
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
									{ make_param("a","Map",Nan::Undefined()) }, 
											static_function_instance_map);
			^ namespace or empty
					^ class name
							^ function name
									^ array of parameter names, types and default values
											^ callback POLY_METHOD
```




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

