{
  "targets": [
	{
		"target_name":"node-overload-resolution",
		"type" : "static_library",
		"include_dirs":[
			"./",
			"<!(node -e \"require('nan')\")"
		],
		"direct_dependent_settings":{
			"include_dirs":[
				"./",
				"<!(node -e \"require('nan')\")"
			],
		},
		"sources":[			
			  "overload_resolution.h"
			, "overload_resolution.cpp"
			
			, "IStructuredObject.h"
			, "IStructuredObject.cpp"
			
			, "FunctionCallbackInfo.h"
			
			, "factory.h"
			, "README.md"
			, "package.json"
		],
	},
    {
      "target_name": "overload-tester",
	  "dependencies":[
		"node-overload-resolution"
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
		
        , "tests/constructor_class_tester.h"
		, "tests/constructor_class_tester.cpp"

		, "tests/or_tester.h"
		, "tests/or_struct_tester.h"
		, "tests/or_two_parameters_tester.h"
		, "tests/or_array_tester.h"
		, "tests/or_default_tester.h"
	  ]
    }
  ]
}