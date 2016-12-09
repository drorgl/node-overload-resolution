#ifndef _O_R_CALLBACK_H_
#define _O_R_CALLBACK_H_

#include <nan.h>

//#include "generic_value_holder.h"

namespace or {
	class generic_value_holder;

	class Callback : public Nan::Callback {
		using Nan::Callback::Call;

	public:
		Callback() : Nan::Callback() {}

		Callback(const v8::Local<v8::Function> &fn) : Nan::Callback(fn) {}

		virtual ~Callback() {}

		

		void Call(std::vector<generic_value_holder> args) {
			if (_calls == nullptr) {
				_calls = std::make_shared<std::vector<std::vector<generic_value_holder>>>();
			}
			
			_calls->push_back(args);
		}


		void post_process() {
			if (_calls != nullptr) {

				//this->Call()
				//#pragma message ("not implemented")
				throw std::exception("not implemented");

				
				//GetReturnValue().Set(_return->Get());
			}
		}

	private:
		std::shared_ptr<std::vector<std::vector<generic_value_holder>>> _calls = nullptr;
	};
}

#endif