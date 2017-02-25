#ifndef _O_R_DATETIME_H_
#define _O_R_DATETIME_H_

#include <nan.h>
//#include <time.h>
#include <chrono>
#include <ctime>
#include <time.h>  

namespace overres {
	class DateTime {
	private:
		std::time_t _datetime;

	public:
		DateTime() {}
		DateTime(v8::Local<v8::Date> date) {
			double n = date->NumberValue();
			
			_datetime = (std::time_t)(n / 1000);
		}

		DateTime(std::time_t datetime) {
			_datetime = datetime;
		}

		DateTime(std::tm &t) {
			_datetime = (double)std::mktime(&t);
		}

		tm to_tm() {
			tm t;
#ifdef WIN32
			gmtime_s(&t, &_datetime);
#else
			gmtime_r(&_datetime, &t);
#endif

			return t;
			
		}

		std::time_t to_time_t() {
			return _datetime;
		}

		v8::Local<v8::Date> to_v8_Date() {
			return Nan::New<v8::Date>(_datetime * 1000).ToLocalChecked();
		}
	};
}

#endif