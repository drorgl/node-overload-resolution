#ifndef _O_R_FUNCTIONCALLBACKINFO_H_
#define _O_R_FUNCTIONCALLBACKINFO_H_

#include "v8.h"

#include "node_modules/nan/nan.h"

namespace or {

	template<typename T>
	class FunctionCallbackInfo {
	public:
		inline int Length() const {
			return _params.size();
		}
		inline v8::Local<v8::Value> operator[](int i) const{
			if (i < _params.size()) {
				return _params[i];
			}
			else {
				return Nan::Undefined();
			}
		}

		inline v8::Local<v8::Function> Callee() const{
			return _info.Callee();
		}
		inline v8::Local<v8::Object> This() const{
			return _info.This();
		}
		inline v8::Local<v8::Object> Holder() const{
			return _info.Holder();
		}
		inline bool IsConstructCall() const{
			return _info.IsConstructCall();
		}
		inline v8::Local<v8::Value> Data() const{
			return _info.Data();
		}
		inline v8::Isolate* GetIsolate() const {
			return _info.GetIsolate();
		}
		inline Nan::ReturnValue<T> GetReturnValue() const {
			return _info.GetReturnValue();
		}

		FunctionCallbackInfo(Nan::NAN_METHOD_ARGS_TYPE &info, std::vector<v8::Local<v8::Value>> &params) :
			_info(info), _params(params) {
			
		}

	protected:

		//friend class overload_resolution;

		Nan::NAN_METHOD_ARGS_TYPE _info;

		std::vector<v8::Local<v8::Value>> &_params;
	};

}
#endif