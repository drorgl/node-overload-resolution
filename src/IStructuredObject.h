#ifndef _TESTER_ISTRUCTURED_OBJECT_H_
#define _TESTER_ISTRUCTURED_OBJECT_H_

#include <nan.h>

class overload_resolution;
namespace overres {class type_system; };

/**
 * @brief Structured Object Interface
 * used as a base class for all structured types to be used as arguments or return values
 * 
 */
class IStructuredObject {

public:
	/**
	 * @brief verifies an object can be of the structured type
	 * 
	 * @param ovres overload resolution type system instance
	 * @param obj v8 object to check if it can be of structured type
	 * @return true if obj can be of structured type
	 * @return false if object cannot be of structured type
	 */
	virtual bool verify(overres::type_system * ovres, v8::Local<v8::Value> obj) = 0;
	virtual bool parse(v8::Local<v8::Value> obj) = 0;
	virtual v8::Local<v8::Value> ToObject() = 0;

	virtual ~IStructuredObject() {}

};


#endif