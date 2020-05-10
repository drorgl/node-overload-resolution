#ifndef _THREADSAFE_QUEUE_H_
#define _THREADSAFE_QUEUE_H_

#include <queue>
#include <mutex>
#include <atomic>

/**
 * @brief threadsafe queue
 * 
 * @tparam T type of items in the queue
 */
template<typename T>
class threadsafe_queue
{
private:
	/**
	 * @brief the underlying std::queue
	 * 
	 */
	std::queue<T> _queue;

	/**
	 * @brief the mutex for accessing the underlying queue
	 * 
	 */
	mutable std::mutex m;

	/**
	 * @brief the queue length
	 * 
	 */
	std::atomic_uint _queue_length;
public:
	/**
	 * @brief Construct a new threadsafe queue instance
	 * 
	 */
	threadsafe_queue() {}

	/**
	 * @brief enqueue an item
	 * 
	 * @param item item to put in the queue
	 */
	void enqueue(T item)
	{
		std::lock_guard<std::mutex> lock(m);
		_queue.push(item);
		_queue_length++;
	}

	/**
	 * @brief dequeue an item
	 * 
	 * @param itemref reference to store the item in
	 * @return true if successfully dequeued an item
	 * @return false if no item is left in the queue
	 */
	bool dequeue(T &itemref)
	{
		std::lock_guard<std::mutex> lock(m);

		bool val = false;
		if (!_queue.empty()){
			_queue_length--;
			T item = _queue.front();
			itemref = item;
			_queue.pop();
			val = true;
		}
		return val;
	}
	
	/**
	 * @brief number of items in the queue
	 * 
	 * @return unsigned int 
	 */
	unsigned int length() {
		return _queue_length;
	}

	/**
	 * @brief clears the queue from all items
	 * 
	 */
	void clear() {
		std::lock_guard<std::mutex> lock(m);
		std::queue<T> empty;
		std::swap(_queue, empty);
		_queue_length = 0;
	}
};


#endif