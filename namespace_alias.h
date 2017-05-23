#ifndef _O_R_OVERLOAD_RESOLUTION_NAMESPACE_ALIAS_H_
#define _O_R_OVERLOAD_RESOLUTION_NAMESPACE_ALIAS_H_

#include "value_converter_base.h"

#include "class_alias.h"

class namespace_alias {
public:
	namespace_alias();

		std::shared_ptr<namespace_alias> add_namespace(const std::string namespace_name);

	std::shared_ptr<class_alias> add_class(const std::string class_name);
};

#endif