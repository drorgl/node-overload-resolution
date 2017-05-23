#ifndef _O_R_OVERLOAD_RESOLUTION_CLASS_ALIAS_H_
#define _O_R_OVERLOAD_RESOLUTION_CLASS_ALIAS_H_

#include "value_converter_base.h"

class class_alias {
public:

	Nan::Persistent<v8::FunctionTemplate, Nan::CopyablePersistentTraits<v8::FunctionTemplate>> function_template;
	std::string ns;
	std::string name;
	std::shared_ptr< overres::value_converter_base> value_converter;
};

#endif