#ifndef _O_R_CALLBACK_H_
#define _O_R_CALLBACK_H_

#include <nan.h>

#include "generic_value_holder.h"

namespace or {
	class generic_value_holder;

	class Callback {
	public:
		Callback() {
			_callback = std::make_shared<Nan::Callback>();
		}

		Callback(const v8::Local<v8::Function> &fn) {
			_callback = std::make_shared<Nan::Callback>(fn);
		}

		virtual ~Callback() {
		}

		v8::Local<v8::Function> GetFunction() const {
			return _callback->GetFunction();
		}

		v8::Local<v8::Value> Call(int argc, v8::Local<v8::Value> argv[]) {
			return _callback->Call(argc, argv);
		}

		void Call(std::vector<std::shared_ptr<generic_value_holder>> args) {
			if (_calls == nullptr) {
				_calls = std::make_shared<std::vector<std::vector<std::shared_ptr<generic_value_holder>>>>();
			}
			
			_calls->push_back(args);
		}


		v8::Local<v8::Value> post_process() {
			v8::Local<v8::Value> return_value;
			if (_calls != nullptr) {
				for (auto cb_vals : *_calls) {
					std::vector<v8::Local<v8::Value>> params;
					for (auto param : cb_vals) {
						params.push_back(param->Get());
					}
					return_value = this->Call(params.size(), &params[0]);
				}
			}

			return return_value;
		}

	private:
		std::shared_ptr<std::vector<std::vector<std::shared_ptr<generic_value_holder>>>> _calls = nullptr;

		std::shared_ptr<Nan::Callback> _callback;
	};
}

#endif