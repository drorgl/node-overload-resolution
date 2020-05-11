#ifndef _O_R_ASYNC_CALLBACK_H_
#define _O_R_ASYNC_CALLBACK_H_



#include "utilities/threadsafe_queue.h"
#include "utilities/uvasync.h"

#include <nan.h>

//#include "generic_value_holder.h"

namespace overres {
	class generic_value_holder;

	/**
	 * @brief Async Callback, similar to callback but allowes other threads to call the v8 callbacks
	 * 
	 * Async callback is different from callback as it allowes other threads to queue callbacks into v8
	 * Its also possible to persist
	 * 
	 * when created, a new uvasync instance should be assigned
	 * all "call"s should be queued
	 * when the "call" is called, a signal is sent
	 * when the callback is called, all queued calls should be flushed
	 * when the callback goes out of scope, the uvasync should be deleted as well
	 * callback should contain  user data of some sort
	 * 
	 */
	class AsyncCallback {

	public:
		/**
		 * @brief Construct a new Async Callback with nop function
		 * 
		 */
		AsyncCallback() 
			:_callback(std::make_shared<Nan::Callback>()){
			_uvasync = std::make_unique<overres_utilities::uvasync>(AsyncCallback::async_uv_callback, this);
		}

		/**
		 * @brief Construct a new Async Callback with v8 function
		 * 
		 * @param fn v8 function
		 */
		explicit AsyncCallback(const v8::Local<v8::Function> &fn)
			:_callback(std::make_shared<Nan::Callback>(fn)) {
			_uvasync = std::make_unique<overres_utilities::uvasync>(AsyncCallback::async_uv_callback, this);
		}

		virtual ~AsyncCallback() {
			_uvasync->set_ref(false);
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
		 * @brief Call the v8 Async Function with arguments
		 * Multiple calls to this function will eventually call the callback multiple times
		 * @note this function does not immediately call the v8 function but waits until the next event loop iteration
		 * 
		 * @param args arguments for the callback
		 */
		void Call(std::vector<std::shared_ptr<generic_value_holder>> args) {
			_calls.enqueue(args);
			_uvasync->signal();
			
		}

		/**
		 * @brief sets strong reference for function, strong reference will prevent the event loop from exiting 
		 * 
		 * @param is_strong 
		 */
		void set_ref(bool is_strong) {
			_uvasync->set_ref(is_strong);
		}
		
	private:
		/**
		 * @brief v8 function call
		 * 
		 * @param argc number of arguments
		 * @param argv array of values
		 * @return v8::Local<v8::Value> 
		 */
		v8::Local<v8::Value> Call(size_t argc, v8::Local<v8::Value> argv[]) {
			Nan::TryCatch tc;
			auto returnValue = _callback->Call(argc, argv);
			if (tc.HasCaught()) {
				returnValue = tc.ReThrow();
			}
			return returnValue;
		}

		/**
		 * @brief Performs the actual callback to v8 function
		 * @note async_process is executed on the next event loop execution
		 * 
		 */
		void async_process() {
			if (!_uvasync->isActive()) {
				return;
			}

			std::vector<std::shared_ptr<generic_value_holder>> call_data;

			while (_calls.dequeue(call_data) ){
				std::vector<v8::Local<v8::Value>> params;
				std::transform(std::begin(call_data), std::end(call_data), std::back_inserter(params), [](const auto param) {
					return param->Get();
				});
				this->Call(params.size(), &params[0]);
			}
		}

		/**
		 * @brief holds the parameters and number of times the function call should be made in the next event loop iteration
		 * 
		 */
		threadsafe_queue<std::vector<std::shared_ptr<generic_value_holder>>> _calls;

		std::shared_ptr<Nan::Callback> _callback;

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
		static void async_uv_callback(uv_async_t* req/*, int status UNUSED*/) {
#else
		static void async_uv_callback(uv_async_t* req,int status /*UNUSED*/) {
#endif
			AsyncCallback* this_ = static_cast<AsyncCallback*>(req->data);

			Nan::HandleScope scope;
			this_->async_process();
		}

		std::unique_ptr< overres_utilities::uvasync> _uvasync;
	};
}

#endif