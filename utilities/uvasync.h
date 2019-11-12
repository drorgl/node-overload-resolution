#ifndef _OR_UV_ASYNC_WRAPPER_
#define _OR_UV_ASYNC_WRAPPER_

#include <uv.h>
#include <atomic>
#include <unordered_set>

namespace overres_utilities {

	class uvasync {
	private:
		static std::unordered_set<uv_async_t*> _inuseasyncs;
		uv_async_t * _async_inst;
		std::atomic<bool> _is_active;
	public:
		uvasync(uv_async_cb callback, void * data);



		bool isActive();

		void signal();

		void set_ref(bool is_strong);

		static void close_handler(uv_handle_t* handle);

		~uvasync();
	};

};
#endif
