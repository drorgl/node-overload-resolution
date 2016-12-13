#ifndef _O_R_FUNCTIONCALLBACKINFO_H_
#define _O_R_FUNCTIONCALLBACKINFO_H_

#include <nan.h>

#include "value_holder.h"
#include "value_converter.h"
#include "generic_value_holder.h"

#include <memory>

struct overload_info;

namespace or {

	template<typename T>
	class FunctionCallbackInfo {
	public:
		inline int Length() const {
			return _params.size();
		}
		inline v8::Local<v8::Value> operator[](int i) const {
			if (i < _params.size()) {
				return _params[i];
			}
			else {
				return Nan::Undefined();
			}
		}

		/*template<typename atT>
		inline std::shared_ptr<value_converter<atT>> at(int i) const {
			return _prefetched[i]
		}*/
		template<typename atT>
		inline atT at(int i) const {
			//attempt to get converted value first
			if (_values.size() > i) {
				return  std::static_pointer_cast<or ::value_holder<atT>>(_values[i])->Value;
			}

			//no converted value, retrieve value_converter and attempt to convert params to atT
			auto argprefetcher = std::static_pointer_cast<or ::value_converter<atT>>(_arguments[i]->value_converter);
#ifdef DEBUG
			if (argprefetcher == nullptr) {
				throw new std::exception("argument value_converter does not match registered type");
			}
#endif
			return argprefetcher->convert(_params[i]);
		}

		inline v8::Local<v8::Function> Callee() const {
			return _info.Callee();
		}
		inline v8::Local<v8::Object> This() const {
			return _info.This();
		}
		inline v8::Local<v8::Object> Holder() const {
			return _info.Holder();
		}
		inline bool IsConstructCall() const {
			return _info.IsConstructCall();
		}
		inline v8::Local<v8::Value> Data() const {
			return _info.Data();
		}
		inline v8::Isolate* GetIsolate() const {
			return _info.GetIsolate();
		}

		inline void SetReturnValue(v8::Local<v8::Value> returnValue) {
			_info.GetReturnValue().Set(returnValue);
		}

		template<typename retT>
		inline void SetReturnValue(retT returnValue) const {
			const_cast<FunctionCallbackInfo<T>*>(this)->_return = std::make_shared<generic_value_holder>();
			_return->Set<retT>(returnValue);
			////Nan::ThrowSyntaxError
		}

		
		inline Nan::ReturnValue<T> GetReturnValue() const {
			if (_return != nullptr) {
				throw std::exception("a return value was already set by SetReturnValue, this is most likely a bug");
			}
			return _info.GetReturnValue();
		}

		FunctionCallbackInfo(Nan::NAN_METHOD_ARGS_TYPE &info, std::vector<v8::Local<v8::Value>> &params, std::vector<std::shared_ptr<overload_info>> &arguments) :
			_info(info), _params(params), _arguments(arguments) {

		}



		//stores a local cache of c++ objects from passed v8 arguments
		void prefetch() {
			for (auto i = 0; i < _arguments.size(); i++) {
				auto oinfo = _arguments[i];

				_values.push_back(_arguments[i]->value_converter->read(_params[i]));
			}
		}

		void post_process() {
			if (_return != nullptr) {
				_info.GetReturnValue().Set(_return->Get());
			}
		}

	protected:

		//friend class overload_resolution;

		Nan::NAN_METHOD_ARGS_TYPE _info;

		//v8 values passed to the function
		std::vector<v8::Local<v8::Value>> &_params;

		//argument info
		std::vector<std::shared_ptr<overload_info>> &_arguments;

		//parsed values, cached before using async methods
		std::vector<std::shared_ptr< or ::value_holder_base>> _values;

		//return values, should be converted back to v8 objects when function returns
		std::shared_ptr<generic_value_holder> _return;
	};

}
#endif