#ifndef _TESTER_NAMESPACE_CONSTRUCTS_H_
#define _TESTER_NAMESPACE_CONSTRUCTS_H_

#include <memory>
#include <string>
#include "../overload_resolution.h"

/** 
 * @addtogroup tests
 * @{
 */

/**
 * @brief example class for testin correct behavior on namespace wrapping
 * 
 */
class namespace_constructs {
public:
	static void Init(std::shared_ptr<namespace_wrap> overload) {
		overload->add_overload("standalone_function_construct", {}, standalone_function_construct);

		auto nc = overload->add_namespace("namespace_construct");
		nc->add_overload("nc_standalone_function_construct", {}, nc_standalone_function_construct_nc);
		nc->add_overload("standalone_function_construct_nc", {}, standalone_function_construct_nc);

	}


	static POLY_METHOD(standalone_function_construct) {
		info.SetReturnValue("standalone_function_construct"s);
	}

	static POLY_METHOD(nc_standalone_function_construct_nc) {
		info.SetReturnValue("nc_standalone_function_construct_nc"s);
	}

	static POLY_METHOD(standalone_function_construct_nc) {
		info.SetReturnValue("standalone_function_construct_nc"s);
	}

};
/** @}*/
#endif