#ifndef _O_R_OVERLOAD_RESOLUTION_OBJECT_TYPE_H_
#define _O_R_OVERLOAD_RESOLUTION_OBJECT_TYPE_H_

#include "value_converter_base.h"

namespace overres {
	struct object_type {
		Nan::Persistent<v8::FunctionTemplate> function_template;
		std::string ns;
		std::string name;
		std::shared_ptr< overres::value_converter_base> value_converter;
	};
}

#endif