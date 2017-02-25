#ifndef _THREADED_TESTER_H_
#define _THREADED_TESTER_H_

#include <vector>
#include <functional>
#include <thread>
#include <atomic>
#include <memory>

#include <uv.h>

class ThreadedTester {
private:
	struct cb_data {
		cb_data(int times_, std::function<void(void)> callbacks_) {
			times = times_;
			callback = callbacks_;
		}
		int times;
		std::function<void(void)> callback;
	};
	std::vector<std::shared_ptr<cb_data>> _callbacks;

	std::unique_ptr<std::thread> _thread;

	std::atomic<bool> _execute;

	void process() {
		if (_callbacks.size() > 0) {
			for (size_t i = 0; i < _callbacks.size(); i++) {
				if (_callbacks[i]->times <= 0) {
					_callbacks.erase(_callbacks.begin() + i);
					return;
				}
				_callbacks[i]->times--;
				_callbacks[i]->callback();
			}
			
		}
	}

	void thread_callback() {
		while (_execute == true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			process();
		}
	}
public:
	ThreadedTester() {
		_execute = true;
		
	}

	void Start() {
		if (_thread == nullptr) {
			_thread = std::make_unique<std::thread>(&ThreadedTester::thread_callback, this);
		}
	}

	~ThreadedTester() {
		_execute = false;
		_thread->join();
	}

	void Enqueue(int times, std::function<void(void)> callback) {
		_callbacks.push_back(std::make_shared<cb_data>( times, callback ));
	}
};

#endif