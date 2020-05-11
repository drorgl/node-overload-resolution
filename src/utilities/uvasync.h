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
		/**
		 * @brief Construct a new uvasync with callback and user data
		 * 
		 * @param callback 
		 * @param data 
		 */
		uvasync(uv_async_cb callback, void * data);


		/**
		 * @brief checks if the uvasync handle is active
		 * handle is always active until closed
		 * 
		 * @return true 
		 * @return false 
		 */
		bool isActive();

		/**
		 * @brief wake up the event loop and call the async callback
		 * 
		 */
		void signal();

		/**
		 * @brief Set the handle as strong or weak
		 * weak handles allow the event loop to exit
		 * 
		 * @param is_strong 
		 */
		void set_ref(bool is_strong);

		static void close_handler(uv_handle_t* handle);

		~uvasync();
	};

};
#endif
