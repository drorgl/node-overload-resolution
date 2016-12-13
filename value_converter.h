#ifndef _O_R_VALUE_CONVERTER_H_
#define _O_R_VALUE_CONVERTER_H_

#include "v8.h"

#include "node_modules/nan/nan.h"

#include "value_converter_base.h"
#include "value_holder.h"

#include "DateTime.h"
#include "Callback.h"
#include "ObjectWrap.h"
#include "IStructuredObject.h"




#include <type_traits>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include <string>

#include "class_typename.h"

namespace or {
	

	//default value

	template<typename T, class = void>
	class prefetcher : public prefetcher_base {
	public:

		virtual T convert(v8::Local<v8::Value> from) {
			DECLARE_CLASS_TYPENAME(T)

#pragma message ("not implemented, need template specialization " T)
			throw std::exception("not implemented, need template specialization for " + Class_TypeName<T>::name);
		}


		virtual v8::Local<v8::Value> convert(T from) {
			DECLARE_CLASS_TYPENAME(T)

#pragma message ("not implemented, need template specialization " T)
			throw std::exception("not implemented, need template specialization for " + Class_TypeName<T>::name);
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

	//Callback

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

	//ObjectWrap

	template<typename T>
	class prefetcher<T*, typename std::enable_if<std::is_base_of<ObjectWrap, T>::value>::type> : public prefetcher_base {
	public:

		virtual T* convert(v8::Local<v8::Value> from) {
			return or::ObjectWrap::Unwrap<T>(from.As<v8::Object>());
		}


		virtual v8::Local<v8::Value> convert(T* from) {
			return from->Wrap();
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<T*>>(from);
			return from_value->Value->Wrap();
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<T*>>();
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

	//IStructuredObject

	template<typename T>
	class prefetcher<std::shared_ptr<T>,typename std::enable_if<std::is_base_of<IStructuredObject,T>::value>::type> : public prefetcher_base {
	public:

		virtual std::shared_ptr<T> convert(v8::Local<v8::Value> from) {
			if (from.IsEmpty() || from->IsUndefined() || from->IsNull()) {
				return nullptr;
			}

			auto struct_instance = std::make_shared<T>();
			struct_instance->parse(from);
			return struct_instance;
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<T> from) {
			if (from == nullptr) {
				return Nan::Null();
			}
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

	//vector/array

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

		static void FreeBufferCallback(char *data, void *hint) {
			delete (std::shared_ptr<std::vector<T>> *) hint;
		}
		
		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::vector<T>> from) {
			if (std::is_same<T, uint8_t>::value) {
				//create a manual instance of shared_ptr to increment the ref counter manually, which will be deleted by FreeBufferCallback when Buffer is free'd
				auto copy_for_ref_inc = new std::shared_ptr<std::vector<T>>(from);

				auto v8buffer = Nan::NewBuffer((char*)&(*from)[0], from->size(),FreeBufferCallback,copy_for_ref_inc);
				return v8buffer.ToLocalChecked();
			}

			auto v8array = Nan::New<v8::Array>();
			auto converter = std::make_shared<prefetcher<T>>();
			for (auto i = 0; i < from->size(); i++) {
				v8array->Set(i, converter->convert( (*from)[i]));
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




	//map <K, V>

	template<typename T>
	class prefetcher<std::shared_ptr<std::map<std::string, T>>> : public prefetcher_base {
	public:

		virtual std::shared_ptr<std::map<std::string, T>> convert(v8::Local<v8::Value> from) {
			if (!from->IsMap()) {
				throw std::exception("converted v8 value does not contain a v8::Map");
			}

			auto converter = std::make_shared<prefetcher<T>>();

			auto map_value = std::make_shared<std::map<std::string, T>>();
			auto from_map = from.As<v8::Map>()->AsArray();
			assert((from_map->Length() % 2) == 0 && "v8::Map::AsArray returned length other than % 2");
			for (auto i = 0; i < from_map->Length(); i+=2) {
				auto key = *Nan::Utf8String(from_map->Get(i));
				auto value = converter->convert(from_map->Get(i + 1));

				(*map_value)[key] = value;
			}

			return map_value;
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::map<std::string,T>> from) {
			auto converter = std::make_shared<prefetcher<T>>();

			auto map_value = v8::Map::New(v8::Isolate::GetCurrent()); //Nan::New<v8::Map>();
			
			for (auto &&kv : *from) {
				map_value->Set(Nan::GetCurrentContext(), Nan::New(kv.first).ToLocalChecked(), converter->convert(kv.second));
			}

			return map_value;
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<std::shared_ptr<std::map<std::string, T>>>>(from);
			return convert(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<std::shared_ptr<std::map<std::string, T>>>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	//map <K, V>

	template<typename K, typename T>
	class prefetcher<std::shared_ptr<std::map<K, T>>> : public prefetcher_base {
	public:

		virtual std::shared_ptr<std::map<K, T>> convert(v8::Local<v8::Value> from) {
			
			if (!from->IsMap()) {
				throw std::exception("converted v8 value does not contain a v8::Map");
			}

			auto value_converter = std::make_shared<prefetcher<T>>();
			auto key_converter = std::make_shared<prefetcher<K>>();

			auto map_value = std::make_shared<std::map<std::string, T>>();
			auto from_map = from.As<v8::Map>()->AsArray();
			assert((from_map->Length() % 2) == 0 && "v8::Map::AsArray returned length other than % 2");
			for (auto i = 0; i < from_map->Length(); i += 2) {
				auto key = key_converter->convert(from_map->Get(i));
				auto value = value_converter->convert(from_map->Get(i + 1));

				(*map_value)[key] = value;
			}

			return map_value;
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::map<K,T>> from) {
			auto value_converter = std::make_shared<prefetcher<T>>();
			auto key_converter = std::make_shared<prefetcher<K>>();

			auto map_value = v8::Map::New(v8::Isolate::GetCurrent()); //Nan::New<v8::Map>();

			for (auto &&kv : *from) {
				map_value->Set(Nan::GetCurrentContext(),key_converter->convert(kv.first), value_converter->convert(kv.second));
			}

			return map_value;
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<std::shared_ptr<std::map<K, T>>>>(from);
			return convert(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<std::shared_ptr<std::map<K, T>>>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};


	//set <T>

	template<typename T>
	class prefetcher<std::shared_ptr<std::set<T>>> : public prefetcher_base {
	public:

		virtual std::shared_ptr<std::set<T>> convert(v8::Local<v8::Value> from) {

			if (!from->IsSet()) {
				throw std::exception("converted v8 value does not contain a v8::Set");
			}

			auto converter = std::make_shared<prefetcher<T>>();

			auto set_value = std::make_shared<std::set<T>>();
			auto from_set = from.As<v8::Set>()->AsArray();
			for (auto i = 0; i < from_set->Length(); i ++) {
				auto value = converter->convert(from_set->Get(i));

				set_value->insert(value);
			}

			return set_value;
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::set<T>> from) {
			auto converter = std::make_shared<prefetcher<T>>();

			auto set_value = v8::Set::New(v8::Isolate::GetCurrent()); //Nan::New<v8::Set>();

			for (auto &&kv : *from) {
				set_value->Add(Nan::GetCurrentContext(), converter->convert(kv));
			}

			return set_value;
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<std::shared_ptr<std::set<T>>>>(from);
			return convert(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<std::shared_ptr<std::set<T>>>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};


	//string

	template<>
	class prefetcher<std::string> : public prefetcher_base {
	public:

		virtual std::string convert(v8::Local<v8::Value> from) {
			return *Nan::Utf8String(from->ToString());
		}

		virtual v8::Local<v8::Value> convert(std::string from) {
			return Nan::New(from).ToLocalChecked();
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

	//int/Number

	template<>
	class prefetcher<int> : public prefetcher_base {
	public:

		virtual int convert(v8::Local<v8::Value> from) {
			return from->IntegerValue();
		}

		virtual v8::Local<v8::Value> convert(int from) {
			return Nan::New(from);
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

	//uint8_t / number

	template<>
	class prefetcher<uint8_t> : public prefetcher_base {
	public:

		virtual uint8_t convert(v8::Local<v8::Value> from) {
			return from->IntegerValue();
		}

		virtual v8::Local<v8::Value> convert(uint8_t from) {
			return Nan::New(from);
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

	//bool

	template<>
	class prefetcher<bool> : public prefetcher_base {
	public:

		virtual int convert(v8::Local<v8::Value> from) {
			return from->BooleanValue();
		}

		virtual v8::Local<v8::Value> convert(bool from) {
			return Nan::New(from);
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


	template<>
	class prefetcher<DateTime> : public prefetcher_base {
	public:

		virtual DateTime convert(v8::Local<v8::Value> from) {
			return DateTime(from.As<v8::Date>());
		}

		virtual v8::Local<v8::Value> convert(DateTime from) {
			return from.to_v8_Date();
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<DateTime> from) {
			return from->to_v8_Date();
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<DateTime>>(from);
			return from_value->Value.to_v8_Date();
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<DateTime>>();
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