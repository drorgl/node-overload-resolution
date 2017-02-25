#ifndef _O_R_FUNCTIONCALLBACKINFO_H_
#define _O_R_FUNCTIONCALLBACKINFO_H_

#include <nan.h>
#include <memory>

#include "value_holder.h"
#include "value_converter.h"
#include "generic_value_holder.h"

#include "overload_info.h"

namespace overres {

	template<typename T>
	class FunctionCallbackInfo {
	public:
		inline int Length() const {
			return _params.size();
		}
		inline v8::Local<v8::Value> operator[](size_t i) const {
			if (is_async) {
				throw std::runtime_error("info[] does not work in async, use at<T> instead");
			}

			if (i < _params.size()) {
				return _params[i];
			}
			else {
				return Nan::Undefined();
			}
		}

		template<typename atT>
		inline atT at(size_t i) const {
			//attempt to get converted value first
			if (_values.size() > i) {
				return  std::dynamic_pointer_cast<overres::value_holder<atT>>(_values[i])->Value;
			}

			//no converted value, retrieve value_converter and attempt to convert params to atT
			auto argprefetcher = std::dynamic_pointer_cast<overres::value_converter<atT>>(_arguments[i]->value_converter);
#ifdef DEBUG
			if (argprefetcher == nullptr) {
				throw std::runtime_error("argument value_converter does not match registered type");
			}
#endif
			return argprefetcher->convert(_params[i]);
		}

		inline v8::Local<v8::Function> Callee() const {
			return _info.Callee();
		}

		template<typename TThis>
		inline TThis This() const{
			if (_this != nullptr && _this->value != nullptr) {
				return  std::dynamic_pointer_cast<overres::value_holder<TThis>>(_this->value)->Value;
			}
			if (_this != nullptr && _this->prefetcher != nullptr) {
				auto argprefetcher = std::dynamic_pointer_cast<overres::value_converter<TThis>>(_this->prefetcher);
#ifdef DEBUG
				if (argprefetcher == nullptr) {
					throw std::runtime_error("argument value_converter does not match registered type");
				}
#endif

				return argprefetcher->convert(this->This());
			}

			throw std::runtime_error("This is not convertible to TThis");

		}

		inline v8::Local<v8::Object> This() const {
			if (is_async) {
				throw std::runtime_error("This does not work in async, use This<T> instead");
			}

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
			_return = std::make_shared<generic_value_holder>(std::make_shared < overres::value_converter<retT>>(), std::make_shared < overres::value_holder<retT>>(returnValue));
		}


		inline Nan::ReturnValue<T> GetReturnValue() const {
			if (is_async) {
				throw std::runtime_error("GetReturnValue() does not work in async, use SetReturnValue<T> instead");
			}
			if (_return != nullptr) {
				throw std::runtime_error("a return value was already set by SetReturnValue, this is most likely a bug");
			}
			return _info.GetReturnValue();
		}

		FunctionCallbackInfo(Nan::NAN_METHOD_ARGS_TYPE &info, std::vector<v8::Local<v8::Value>> &params, std::vector<std::shared_ptr<overload_info>> &arguments, std::shared_ptr< overres::value_converter_base> this_converter, bool async) :
			is_async(async), _info(info), _params(params), _arguments(arguments) {

			if (this_converter != nullptr) {
				_this = std::make_shared<generic_value_holder>();
				_this->prefetcher = this_converter;
			}
		}



		//stores a local cache of c++ objects from passed v8 arguments
		void prefetch() {
			//Store This
			if (_this != nullptr && _this->prefetcher != nullptr) {
				_this->value= _this->prefetcher->read(_info.This());
			}


			_values.resize(_arguments.size());

			for (size_t i = 0; i < _arguments.size(); i++) {
				if (_params.size() > i) {
					auto converted_param = _arguments[i]->value_converter->read(_params[i]);

					//when executing in async mode
					if (is_async) {
						//functions should know they are async
						if (_arguments[i]->type == "Function") {
							auto func = std::dynamic_pointer_cast<overres::value_holder< std::shared_ptr< overres::Callback>>>(converted_param);
							assert(func != nullptr && "Function is not overres::Callback");
							func->Value->is_async = true;
						}
					}

					_values[i] = converted_param;
				}
			}
		}

		void post_process() {
			if (_return != nullptr && !is_async) {
				_info.GetReturnValue().Set(_return->Get());
			}

			//Call all callbacks post process
			//if (is_async) {
			for (size_t i = 0; i < _arguments.size(); i++) {
				if ((_arguments[i]->type == "Function") && (_values.size() > i)) {
					auto func = std::dynamic_pointer_cast<overres::value_holder< std::shared_ptr< overres::Callback>>>(_values[i]);
					assert(func != nullptr && "Function is not overres::Callback");
					func->Value->post_process();
				}
			}
			//}
		}

		std::shared_ptr<generic_value_holder> Return() {
			return _return;
		}


		//indicator if call is being executed in async
		const bool is_async;

	protected:

		Nan::NAN_METHOD_ARGS_TYPE _info;

		//v8 values passed to the function
		std::vector<v8::Local<v8::Value>> &_params;

		//argument info
		std::vector<std::shared_ptr<overload_info>> &_arguments;

		//parsed values, cached before using async methods
		std::vector<std::shared_ptr< overres::value_holder_base>> _values;

		//return values, should be converted back to v8 objects when function returns
		mutable std::shared_ptr<generic_value_holder> _return;

		//"This" holder
		std::shared_ptr<generic_value_holder> _this;
	};

}
#endif