#ifndef _O_R_CALLBACK_H_
#define _O_R_CALLBACK_H_

#include <nan.h>

#include "generic_value_holder.h"

namespace overres {
	/**
	 * @brief callback holds a javascript function and the parameters to call it with
	 * 
	 * @note see AsyncCallback as well
	 * 
	 */
	class Callback {

	public:
		/**
		 * @brief Construct a new Callback instance with NOP function
		 * 
		 */
		Callback():
			_callback(std::make_shared<Nan::Callback>()),
			is_async(false) {
			
		}

		/**
		 * @brief Construct a new Callback instance with v8 function
		 * 
		 * @param fn 
		 */
		explicit Callback(const v8::Local<v8::Function> &fn):
			_callback(std::make_shared<Nan::Callback>(fn)),
			is_async(false) {
			
		}

		virtual ~Callback() {
		}

		/**
		 * @brief Get the v8 Function 
		 * 
		 * @return v8::Local<v8::Function> 
		 */
		v8::Local<v8::Function> GetFunction() const {
			return _callback->GetFunction();
		}

		/**
		 * @brief Call v8 function style
		 * 
		 * @param argc number of arguments
		 * @param argv array of values
		 * @return v8::Local<v8::Value> 
		 */
		v8::Local<v8::Value> Call(int argc, v8::Local<v8::Value> argv[]) {
			Nan::TryCatch tc;
			auto returnValue = _callback->Call(argc, argv);
			if (tc.HasCaught()) {
				returnValue = tc.ReThrow();
			}
			return returnValue;
		}

		/**
		 * @brief Call C++ function style
		 * 
		 * @param args array of arguments
		 */
		void Call(std::vector<std::shared_ptr<generic_value_holder>> args) {
			if (!is_async) {
				std::vector<v8::Local<v8::Value>> params;
				std::transform(std::begin(args), std::end(args), std::back_inserter(params), [](auto param) {
					return param->Get();
					});
				/*for (auto param : args) {
					params.push_back(param->Get());
				}*/
				this->Call(params.size(), &params[0]);

				//TODO: how to handle callback return values?
				return;
			}

			if (_calls == nullptr) {
				_calls = std::make_shared<std::vector<std::vector<std::shared_ptr<generic_value_holder>>>>();
			}
			
			_calls->push_back(args);
		}

		/**
		 * @brief post process is called when the time comes for executing the callback
		 * 
		 * @return v8::Local<v8::Value> return value from the javascript function
		 */
		v8::Local<v8::Value> post_process() {
			v8::Local<v8::Value> return_value;
			if (_calls != nullptr) {
				for (auto cb_vals : *_calls) {
					std::vector<v8::Local<v8::Value>> params;
					std::transform(std::begin(cb_vals), std::end(cb_vals), std::back_inserter(params), [](auto param) {
						return param->Get();
						});
					/*for (auto param : cb_vals) {
						params.push_back(param->Get());
					}*/
					return_value = this->Call(params.size(), &params[0]);
				}
			}

			return return_value;
		}
		
		
		bool is_async;

	private:
		std::shared_ptr<std::vector<std::vector<std::shared_ptr<generic_value_holder>>>> _calls = nullptr;

		std::shared_ptr<Nan::Callback> _callback;
	};
}

#endif