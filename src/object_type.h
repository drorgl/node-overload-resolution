#ifndef _O_R_OVERLOAD_RESOLUTION_OBJECT_TYPE_H_
#define _O_R_OVERLOAD_RESOLUTION_OBJECT_TYPE_H_

#include "value_converter_base.h"

namespace overres {
	/**
	 * @brief Container for registered class types
	 * 
	 */
	struct object_type {
		/**
		 * @brief Class function template
		 * 
		 */
		Nan::Persistent<v8::FunctionTemplate> function_template;

		/**
		 * @brief namespace of the registered type
		 * 
		 */
		std::string ns;

		/**
		 * @brief name of the registered type
		 * 
		 */
		std::string name;

		/**
		 * @brief Value converter for the registered type
		 * 
		 */
		std::shared_ptr< overres::value_converter_base> value_converter;
	};
}

#endif