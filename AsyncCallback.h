#ifndef _O_R_ASYNC_CALLBACK_H_
#define _O_R_ASYNC_CALLBACK_H_

// Async callback is different from callback as it allowes other threads to queue callbacks into v8
// Its also possible to persist

//when created, a new uvasync instance should be assigned
//all "call"s should be queued
//when the "call" is called, a signal is sent
//when the callback is called, all queued calls should be flushed
//when the callback goes out of scope, the uvasync should be deleted as well
//callback should contain  user data of some sort

#include "utilities/threadsafe_queue.h"
#include "utilities/uvasync.h"

#include <nan.h>

#include "generic_value_holder.h"

namespace or {
	class generic_value_holder;

	class AsyncCallback {

	public:
		AsyncCallback() {
			_callback = std::make_shared<Nan::Callback>();
			_uvasync = std::make_unique<or_utilities::uvasync>(AsyncCallback::async_uv_callback, this);
		}

		AsyncCallback(const v8::Local<v8::Function> &fn) {
			_callback = std::make_shared<Nan::Callback>(fn);
			_uvasync = std::make_unique<or_utilities::uvasync>(AsyncCallback::async_uv_callback, this);
		}

		virtual ~AsyncCallback() {
			_uvasync->set_ref(false);
		}

		v8::Local<v8::Function> GetFunction() const {
			return _callback->GetFunction();
		}

		void Call(std::vector<std::shared_ptr<generic_value_holder>> args) {
			_calls.enqueue(args);
			_uvasync->signal();
			
		}

		// sets strong reference for function, strong reference will wait until instance is disposed before exiting 
		void set_ref(bool is_strong) {
			_uvasync->set_ref(is_strong);
		}
		
	private:
		v8::Local<v8::Value> Call(int argc, v8::Local<v8::Value> argv[]) {
			Nan::TryCatch tc;
			auto returnValue = _callback->Call(argc, argv);
			if (tc.HasCaught()) {
				returnValue = tc.ReThrow();
			}
			return returnValue;
		}

		void async_process() {
			if (!_uvasync->isActive()) {
				return;
			}

			std::vector<std::shared_ptr<generic_value_holder>> call_data;

			while (_calls.dequeue(call_data) ){
				std::vector<v8::Local<v8::Value>> params;
				for (auto param : call_data) {
					params.push_back(param->Get());
				}
				this->Call(params.size(), &params[0]);
			}
		}

		threadsafe_queue<std::vector<std::shared_ptr<generic_value_holder>>> _calls;

		std::shared_ptr<Nan::Callback> _callback;

		static void async_uv_callback(uv_async_t* req) {
			AsyncCallback* this_ = static_cast<AsyncCallback*>(req->data);

			Nan::HandleScope scope;
			this_->async_process();
		}

		std::unique_ptr< or_utilities::uvasync> _uvasync;
	};
}

#endif