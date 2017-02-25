#ifndef _O_R_ASYNC_WORKER_H_
#define _O_R_ASYNC_WORKER_H_

#include <nan.h>
#include <uv.h>
#include "overload_resolution_types.h"

namespace overres {

	class async_worker {
	public:
		uv_work_t request;

		async_worker(PolyFunctionCallback &func, std::shared_ptr< overres::FunctionCallbackInfo<v8::Value>> params, std::shared_ptr< overres::Callback> async_cb) :_func(func), _async_cb(async_cb), _params(params) {
			request.data = this;
			_params->prefetch();
		}

		void execute() {
			try {
				_func(*_params);
			}
			catch (std::exception &ex) {
				_error = ex.what();
			}
		}

		void complete() {
			Nan::HandleScope scope;

			try {
				_params->post_process();
			}
			catch (std::exception &ex) {
				_error = ex.what();
			}


			//TODO: !!!!!!!!!!! call ALL callbacks post process
			

			//TODO: call the async callback function
			if (_error == "") {
				v8::Local<v8::Value> argv[] = {
					Nan::Null(),
					_params->Return()->Get()
				};

				_async_cb->Call(2, argv);
			}
			else {
				v8::Local<v8::Value> argv[] = {
					Nan::New(_error).ToLocalChecked(),
					Nan::Null()
				};

				_async_cb->Call(2, argv);
			}

			/*if (_error != "") {
				Nan::ThrowError(Nan::New(_error).ToLocalChecked());
			}*/
			_async_cb->post_process();
		}

	protected:
		PolyFunctionCallback &_func;
		std::shared_ptr< overres::FunctionCallbackInfo<v8::Value>> _params;
		std::string _error;
		std::shared_ptr< overres::Callback> _async_cb;
	};

	inline void async_execute(uv_work_t* req) {
		async_worker *worker = static_cast<async_worker*>(req->data);
		worker->execute();
	}

	inline void async_execute_complete(uv_work_t* req) {
		async_worker* worker = static_cast<async_worker*>(req->data);
		worker->complete();
		delete worker;
	}

	void async_queue_worker(async_worker* worker) {
		uv_queue_work(
			uv_default_loop()
			, &worker->request
			, async_execute
			, reinterpret_cast<uv_after_work_cb>(async_execute_complete)
			);
	}

	void queue_async_polyfunction(PolyFunctionCallback &func, std::shared_ptr< overres::FunctionCallbackInfo<v8::Value>> params, std::shared_ptr<overres::Callback> async_cb) {
		auto async_instance = new async_worker(func, params, async_cb);
		async_queue_worker(async_instance);
	}

}

#endif