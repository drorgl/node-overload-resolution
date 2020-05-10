{
  "targets": [
	{
		"target_name":"node-overload-resolution",
		"type" : "static_library",
		"include_dirs":[
			"./",
			"<!(node -e \"require('nan')\")"
		],
		"dependencies":[
			"<!(node -e \"require('@drorgl/node-addon-tracer')\"):node-addon-tracer"
		  ],
		"direct_dependent_settings":{
			"include_dirs":[
				"./",
				"<!(node -e \"require('nan')\")"
			],
		},
		"sources":[			
			  "src/overload_resolution.h"
			, "src/overload_resolution.cpp"
			
			, "src/overload_executor.cpp"
			, "src/overload_executor.h"
						
			, "src/class_wrap.cpp"
			, "src/class_wrap.h"
			
			, "src/namespace_wrap.cpp"
			, "src/namespace_wrap.h"
						
			, "src/function_arguments.h"
			, "src/function_arguments.cpp"
			
			, "src/function_rank_cache.h"
			, "src/function_rank_cache.cpp"
			
			, "src/type_system.h"
			, "src/type_system.cpp"
			
			, "src/overload_resolution_types.h"
			
			, "src/object_type.h"
			, "src/overload_info.h"
			, "src/overload_info.cpp"
			
			
			, "src/IStructuredObject.h"
			
			, "src/FunctionCallbackInfo.h"
			
			, "src/ObjectWrap.cpp"
			, "src/ObjectWrap.h"
			
			, "src/AsyncCallback.h"
			, "src/Callback.h"
			
			, "src/DateTime.h"
			
			, "src/value_converter_base.h"
			, "src/value_converter.h"
			, "src/value_holder.h"
			
			, "src/generic_value_holder.h"
			
			, "src/factory.h"
			
			, "src/class_typename.h"
			
			, "src/async_worker.h"
			, "src/utilities/threadsafe_queue.h"
			, "src/utilities/uvasync.cpp"
			, "src/utilities/uvasync.h"
			
			, "README.md"
			, "package.json"
		],
	},
    {
      "target_name": "overload-tester",
	  "dependencies":[
		"node-overload-resolution",
		"<!(node -e \"require('@drorgl/node-addon-tracer')\"):node-addon-tracer"
	  ],
      "sources": [ 
		  "tests/tester.cc"
		, "tests/tester.js"
		, "tests/base_class.h"
		, "tests/base_class.cpp"
		
		, "tests/derived_class.h"
		, "tests/derived_class.cpp"
		
		, "tests/struct_A.h"
		, "tests/struct_A.cpp"
		
		, "tests/struct_B.h"
		, "tests/struct_B.cpp"
		
		, "tests/return_struct.h"
		, "tests/return_struct.cpp"
		
        , "tests/constructor_class_tester.h"
		, "tests/constructor_class_tester.cpp"

		, "tests/or_tester.h"
		, "tests/or_struct_tester.h"
		, "tests/or_two_parameters_tester.h"
		, "tests/or_array_tester.h"
		, "tests/or_default_tester.h"
		, "tests/or_value_converter.h"
		
		, "tests/namespace_constructs.h"
		
		, "tests/class_constructs.h"
		, "tests/class_constructs.cpp"
		
		, "tests/threaded_tester.h"
	  ]
    }
  ]
}