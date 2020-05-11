#ifndef _O_R_OBJECTWRAP_H_
#define _O_R_OBJECTWRAP_H_

#include <nan.h>


namespace overres {
	/** 
	 * @addtogroup overload_resolution
	 * @{
	 */


	/**
	 * @brief Base Class for implementing Overload Resolution Classes
	 * all Overload Resolution Classes should inherit from this class
	 */
	class ObjectWrap : public Nan::ObjectWrap {
	public:

		ObjectWrap() : Nan::ObjectWrap() {}

		using Nan::ObjectWrap::Wrap;

		/**
		 * @brief Wrap current instance into a v8 value
		 * 
		 * @return v8::Local<v8::Object> 
		 */
		v8::Local<v8::Object> Wrap();

		/**
		 * @brief Unwrap v8 value into an instance of T
		 * 
		 * @tparam T type of underlying C++ object
		 * @param handle the v8 value that should be unwrapped
		 * @return T* reference to underlying C++ instance
		 */
		template <class T>
		static inline T* Unwrap(v8::Local<v8::Object> handle) {
			return Nan::ObjectWrap::Unwrap<T>(handle);
		}

		virtual ~ObjectWrap() override;
		
		virtual v8::Local<v8::Function> get_constructor() = 0;
	};

	/** @}*/
};



#endif