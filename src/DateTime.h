#ifndef _O_R_DATETIME_H_
#define _O_R_DATETIME_H_

#include <nan.h>
//#include <time.h>
#include <chrono>
#include <ctime>
#include <time.h>  

namespace overres {
	/**
	 * @brief DateTime type for V8 and std::time_t conversion
	 * 
	 */
	class DateTime {
	private:
		std::time_t _datetime;

	public:
		DateTime() {}

		/**
		 * @brief Construct a new Date Time object from v8 date
		 * 
		 * @param date 
		 */
		explicit DateTime(v8::Local<v8::Date> date) :
			_datetime ((std::time_t)(Nan::To<double>(date).FromJust() / 1000)) {
		}

		/**
		 * @brief Construct a new Date Time object from std::time_t
		 * 
		 * @param datetime 
		 */
		explicit DateTime(std::time_t datetime):
			_datetime(datetime){
		}

		/**
		 * @brief Construct a new Date Time object from std::tm
		 * 
		 * @param t 
		 */
		explicit DateTime(std::tm &t):
			_datetime((std::time_t)std::mktime(&t) ){
		}

		/**
		 * @brief convert to tm
		 * 
		 * @return tm 
		 */
		tm to_tm() {
			tm t;
#ifdef WIN32
			gmtime_s(&t, &_datetime);
#else
			gmtime_r(&_datetime, &t);
#endif

			return t;
			
		}

		/**
		 * @brief convert to std::time_t
		 * 
		 * @return std::time_t 
		 */
		std::time_t to_time_t() {
			return _datetime;
		}

		/**
		 * @brief convert to v8 date
		 * 
		 * @return v8::Local<v8::Date> 
		 */
		v8::Local<v8::Date> to_v8_Date() {
			return Nan::New<v8::Date>(double(_datetime * 1000)).ToLocalChecked();
		}
	};
}

#endif