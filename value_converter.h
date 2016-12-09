#ifndef _O_R_VALUE_CONVERTER_H_
#define _O_R_VALUE_CONVERTER_H_

#include "v8.h"

#include "node_modules/nan/nan.h"



#include "Callback.h"
#include "ObjectWrap.h"
#include "IStructuredObject.h"

#include "value_holder.h"

#include <type_traits>
#include <memory>

namespace or {
	//class Callback;
	//class ObjectWrap;
	//class IStructuredObject;

	class prefetcher_base {
	public:
		prefetcher_base() {}
		virtual ~prefetcher_base() = default;

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) = 0;

		virtual v8::Local<v8::Value> convert(std::shared_ptr< value_holder_base> from) = 0;
	};

	template<typename T, class = void>
	class prefetcher : public prefetcher_base {
	public:

		virtual T convert(v8::Local<v8::Value> from) {
#pragma message ("not implemented, need template specialization " T)
			throw std::exception("not implemented, need template specialization for T");
		}


		virtual v8::Local<v8::Value> convert(T from) {
			return Nan::New(from);
		}

		//virtual v8::Local<v8::Value> convert(std::shared_ptr<T> from) {
		//	return Nan::New(*from);
		//}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<T>>(from);
			return Nan::New(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<T>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};


	template<typename T>
	class prefetcher<std::shared_ptr<T>, typename std::enable_if<std::is_base_of<Callback, T>::value>::type> : public prefetcher_base {
	public:

		virtual std::shared_ptr<T> convert(v8::Local<v8::Value> from) {
			if (!from->IsFunction()) {
				throw std::exception("attempting to convert a non-function to Callback");
			}
			return std::make_shared<T>(from.As<v8::Function>());
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<T> from) {
			return from->GetFunction();
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<std::shared_ptr<T>>>(from);
			return from_value->Value->GetFunction();
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<std::shared_ptr<T>>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	template<typename T>
	class prefetcher<std::shared_ptr<T>, typename std::enable_if<std::is_base_of<ObjectWrap, T>::value>::type> : public prefetcher_base {
	public:

		virtual std::shared_ptr<T> convert(v8::Local<v8::Value> from) {
			return std::make_shared<T>();
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<T> from) {
			return from->Wrap();
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<std::shared_ptr<T>>>(from);
			return from_value->Value->Wrap();
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<std::shared_ptr<T>>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	template<typename T>
	class prefetcher<std::shared_ptr<T>,typename std::enable_if<std::is_base_of<IStructuredObject,T>::value>::type> : public prefetcher_base {
	public:

		virtual std::shared_ptr<T> convert(v8::Local<v8::Value> from) {
			return nullptr;
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<T> from) {
			return from->ToObject();
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<std::shared_ptr<T>>>(from);
			return from_value->Value->ToObject();
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<std::shared_ptr<T>>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	template<typename T>
	class prefetcher<std::shared_ptr<std::vector<T>>> : public prefetcher_base {
	public:

		virtual std::shared_ptr<std::vector<T>> convert(v8::Local<v8::Value> from) {
			if (from->IsArray()) {
				auto arr = std::make_shared<std::vector<T>>();
				auto converter = std::make_shared<prefetcher<T>>();
				auto fromArray = from.As<v8::Array>();
				for (auto i = 0; i < fromArray->Length(); i++) {
					arr->push_back(converter->convert(fromArray->Get(i)));
				}

				return arr;
			}

			if (from->IsArrayBuffer() || from->IsArrayBufferView() || from->IsTypedArray()) {
				auto v8buffer = (T*)node::Buffer::Data(from);
				auto v8bufferlength = node::Buffer::Length(from);

				auto arr = std::make_shared<std::vector<T>>(v8buffer, v8buffer + v8bufferlength);

				return arr;
			}
			
			throw std::exception("converted v8 value does not contain an array or buffer");
		}

		
		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::vector<T>> from) {
			if (std::is_same<T, uint8_t>::value) {
				//std::shared_ptr<std::vector<uint8_t>> x;
				//x.get()->size()
				auto v8buffer = Nan::NewBuffer((char*)&(from.get()[0]), from.get()->size());
				return v8buffer.ToLocalChecked();
			}

			auto v8array = Nan::New<v8::Array>();
			auto converter = std::make_shared<prefetcher<T>>();
			for (auto i = 0; i < from.get()->size(); i++) {
				//v8array->Set(i, converter->convert( from.get()[i]));
			}
			return v8array;
			
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<std::shared_ptr<std::vector<T>>>>(from);
			return convert(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<std::shared_ptr<std::vector<T>>>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};





	template<>
	class prefetcher<std::string> : public prefetcher_base {
	public:

		virtual std::string convert(v8::Local<v8::Value> from) {
			return *Nan::Utf8String(from->ToString());
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::string> from) {
			return Nan::New(*from).ToLocalChecked();
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<std::string>>(from);
			return Nan::New(from_value->Value).ToLocalChecked();
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<std::string>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	template<>
	class prefetcher<int> : public prefetcher_base {
	public:

		virtual int convert(v8::Local<v8::Value> from) {
			return from->IntegerValue();
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<int> from) {
			return Nan::New(*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<int>>(from);
			return Nan::New(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<int>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	template<>
	class prefetcher<uint8_t> : public prefetcher_base {
	public:

		virtual uint8_t convert(v8::Local<v8::Value> from) {
			return from->IntegerValue();
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<uint8_t> from) {
			return Nan::New(*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<uint8_t>>(from);
			return Nan::New(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<uint8_t>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	template<>
	class prefetcher<bool> : public prefetcher_base {
	public:

		virtual int convert(v8::Local<v8::Value> from) {
			return from->BooleanValue();
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<bool> from) {
			return Nan::New(*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<bool>>(from);
			return Nan::New(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<bool>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};


	/*template<>
	class prefetcher<Nan::Callback> : public prefetcher_base {
	public:

		virtual Nan::Callback convert(v8::Local<v8::Value> from) {
			return Nan::Callback(from.As<v8::Function>());
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<Nan::Callback> from) {
			return Nan::Undefined();
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<Nan::Callback>>(from);
			return Nan::Undefined();
		}
	};*/

	//template<typename T>
	//class prefetcher : public prefetcher_base{
	//public:
	//	T* convert(v8::Local<v8::Value> from) {
	//		assert(from->IsObject() && "not a v8::Object for c++ object conversion");
	//		auto obj = from.As<v8::Object>();
	//		assert(!from.IsEmpty() && "empty");
	//		assert(obj->InternalFieldCount() > 0 && "not a C++ object");

	//		void* ptr = obj->GetAlignedPointerFromInternalField(0);
	//		return (T*)(ptr);
	//	}

	//	v8::Local<v8::Value> convert(T* from) {
	//		return Nan::Undefined();
	//	}

	//	v8::Local<v8::Value> convert(std::shared_ptr<T> from) {
	//		return Nan::Undefined();
	//	}

	//	v8::Local<v8::Value> convert(value_holder<T> from) {
	//		return Nan::Undefined();
	//	}

	//	virtual v8::Local<v8::Value> convert(std::shared_ptr< value_holder_base> from) {
	//		auto from_value = std::dynamic_pointer_cast<value_holder<T>>(from);
	//		return Nan::Undefined();
	//	}

	//	prefetcher() : prefetcher_base() {}

	//	virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
	//		auto parsed_value = std::make_shared<value_holder<T>>();
	//		parsed_value->Value = convert(val);
	//		return parsed_value;
	//	}

	//	virtual ~prefetcher() {}
	//};

	//
	//template<>
	//class prefetcher<IStructuredObject *> : public prefetcher_base {
	//public:
	//	std::shared_ptr<IStructuredObject> convert(v8::Local<v8::Value> from) {
	//		//return from->IntegerValue();
	//		return nullptr;
	//	}

	//	v8::Local<v8::Value> convert(IStructuredObject *from) {
	//		return from->ToObject();
	//	}

	//	v8::Local<v8::Value> convert(std::shared_ptr<IStructuredObject> from) {
	//		if (from == nullptr) {
	//			return Nan::Undefined();
	//		}
	//		return from->ToObject();
	//	}

	//	v8::Local<v8::Value> convert(value_holder<IStructuredObject *> from) {
	//		
	//		return from.Value->ToObject();
	//	}


	//	virtual v8::Local<v8::Value> convert(std::shared_ptr< value_holder_base> from) {
	//		auto from_value = std::dynamic_pointer_cast<value_holder<IStructuredObject>>(from);
	//		return from_value->Value->ToObject();
	//	}

	//	virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
	//		auto parsed_value = std::make_shared<value_holder<std::shared_ptr<IStructuredObject>>>();
	//		parsed_value->Value = convert(val);
	//		return parsed_value;
	//	}

	//	prefetcher() : prefetcher_base() {}

	//	virtual ~prefetcher() {}
	//};


	//

	//template<>
	//class prefetcher<int> : public prefetcher_base {
	//public:
	//	int convert(v8::Local<v8::Value> from) {
	//		return from->IntegerValue();
	//	}

	//	v8::Local<v8::Value> convert(int from) {
	//		return Nan::New(from);
	//	}

	//	v8::Local<v8::Value> convert(std::shared_ptr<int> from) {
	//		if (from == nullptr) {
	//			return Nan::Undefined();
	//		}
	//		return Nan::New(*from);
	//	}

	//	v8::Local<v8::Value> convert(value_holder<int> from) {
	//		return Nan::New(from.Value);
	//	}

	//	virtual v8::Local<v8::Value> convert(std::shared_ptr< value_holder_base> from) {
	//		auto from_value = std::dynamic_pointer_cast<value_holder<int>>(from);
	//		return Nan::New(from_value->Value);
	//	}

	//	virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
	//		auto parsed_value = std::make_shared<value_holder<int>>();
	//		parsed_value->Value = convert(val);
	//		return parsed_value;
	//	}

	//	prefetcher() : prefetcher_base() {}

	//	virtual ~prefetcher() {}
	//};

	//template<>
	//class prefetcher<double> : public prefetcher_base {
	//public:
	//	double convert(v8::Local<v8::Value> from) {
	//		return from->IntegerValue();
	//	}

	//	v8::Local<v8::Value> convert(double from) {
	//		return Nan::New(from);
	//	}

	//	v8::Local<v8::Value> convert(std::shared_ptr<double> from) {
	//		if (from == nullptr) {
	//			return Nan::Undefined();
	//		}
	//		return Nan::New(*from);
	//	}

	//	v8::Local<v8::Value> convert(value_holder<double> from) {
	//		return Nan::New(from.Value);
	//	}

	//	virtual v8::Local<v8::Value> convert(std::shared_ptr< value_holder_base> from) {
	//		auto from_value = std::dynamic_pointer_cast<value_holder<double>>(from);
	//		return Nan::New(from_value->Value);
	//	}

	//	virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
	//		auto parsed_value = std::make_shared<value_holder<double>>();
	//		parsed_value->Value = convert(val);
	//		return parsed_value;
	//	}

	//	prefetcher() : prefetcher_base() {}

	//	virtual ~prefetcher() {}
	//};

	//template<>
	//class prefetcher<bool> : public prefetcher_base {
	//public:
	//	bool convert(v8::Local<v8::Value> from) {
	//		return from->IntegerValue();
	//	}

	//	v8::Local<v8::Value> convert(bool from) {
	//		return Nan::New(from);
	//	}

	//	v8::Local<v8::Value> convert(std::shared_ptr<bool> from) {
	//		if (from == nullptr) {
	//			return Nan::Undefined();
	//		}
	//		return Nan::New(*from);
	//	}

	//	v8::Local<v8::Value> convert(value_holder<bool> from) {
	//		return Nan::New(from.Value);
	//	}

	//	virtual v8::Local<v8::Value> convert(std::shared_ptr< value_holder_base> from) {
	//		auto from_value = std::dynamic_pointer_cast<value_holder<bool>>(from);
	//		return Nan::New(from_value->Value);
	//	}

	//	virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
	//		auto parsed_value = std::make_shared<value_holder<bool>>();
	//		parsed_value->Value = convert(val);
	//		return parsed_value;
	//	}

	//	prefetcher() : prefetcher_base() {}

	//	virtual ~prefetcher() {}
	//};

	//template<>
	//class prefetcher<std::string> : public prefetcher_base {
	//public:

	//	std::string convert(v8::Local<v8::Value> from) {
	//		return *Nan::Utf8String(from->ToString());
	//	}

	//	v8::Local<v8::Value> convert(std::string from) {
	//		return Nan::New(from).ToLocalChecked();
	//	}

	//	v8::Local<v8::Value> convert(std::shared_ptr<std::string> from) {
	//		if (from == nullptr) {
	//			return Nan::Undefined();
	//		}
	//		return Nan::New(*from).ToLocalChecked();
	//	}

	//	v8::Local<v8::Value> convert(value_holder<std::string> from) {
	//		return Nan::New(from.Value).ToLocalChecked();
	//	}

	//	virtual v8::Local<v8::Value> convert(std::shared_ptr< value_holder_base> from) {
	//		auto from_value = std::dynamic_pointer_cast<value_holder<std::string>>(from);
	//		return Nan::New(from_value->Value).ToLocalChecked();
	//	}

	//	virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
	//		auto parsed_value = std::make_shared<value_holder<std::string>>();
	//		parsed_value->Value = convert(val);
	//		return parsed_value;
	//	}

	//	prefetcher() : prefetcher_base() {}

	//	virtual ~prefetcher() {}
	//};




}
#endif