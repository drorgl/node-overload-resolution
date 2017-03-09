#ifndef _O_R_VALUE_CONVERTER_H_
#define _O_R_VALUE_CONVERTER_H_

//#include "v8.h"

#include <nan.h>

#include <type_traits>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include <string>

#include "value_converter_base.h"
#include "value_holder.h"

#include "DateTime.h"
#include "Callback.h"
#include "AsyncCallback.h"
#include "ObjectWrap.h"
#include "IStructuredObject.h"


#include "class_typename.h"

using namespace std::literals::string_literals;

namespace overres {
	typedef unsigned short ushort;

	//default value

	template<typename T, class = void>
	class value_converter : public value_converter_base {
	public:

		virtual T convert(v8::Local<v8::Value> from) {
//#pragma message "not implemented, need template specialization "
			throw std::runtime_error(("not implemented, need template specialization for "s + GetTypeName<T>()).c_str());
		}


		virtual v8::Local<v8::Value> convert(T from) {
//#pragma message "not implemented, need template specialization "
			throw std::runtime_error(("not implemented, need template specialization for "s + GetTypeName<T>()).c_str());
		}

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
	class value_converter<std::shared_ptr<T>, typename std::enable_if<std::is_base_of<Callback, T>::value>::type> : public value_converter_base {
	public:

		virtual std::shared_ptr<T> convert(v8::Local<v8::Value> from) {
			if (from->IsNull() || from->IsUndefined()) {
				return nullptr;
			}

			if (!from->IsFunction()) {
				throw std::runtime_error("attempting to convert a non-function to Callback");
			}
			return std::make_shared<T>(from.As<v8::Function>());
		}

		static void EmptyFunctionCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<T> from) {
			if (from == nullptr) {
				return Nan::New<v8::Function>(EmptyFunctionCallback);
			}
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

	//async callback


	template<typename T>
	class value_converter<std::shared_ptr<T>, typename std::enable_if<std::is_base_of<AsyncCallback, T>::value>::type> : public value_converter_base {
	public:

		virtual std::shared_ptr<T> convert(v8::Local<v8::Value> from) {
			if (from->IsNull() || from->IsUndefined()) {
				return nullptr;
			}

			if (!from->IsFunction()) {
				throw std::runtime_error("attempting to convert a non-function to Callback");
			}
			return std::make_shared<T>(from.As<v8::Function>());
		}

		static void EmptyFunctionCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<T> from) {
			if (from == nullptr) {
				return Nan::New<v8::Function>(EmptyFunctionCallback);
			}
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
	class value_converter<T*, typename std::enable_if<std::is_base_of<ObjectWrap, T>::value>::type> : public value_converter_base {
	public:

		virtual T* convert(v8::Local<v8::Value> from) {
			if (from.IsEmpty() || from->IsNull() || from->IsUndefined()) {
				return NULL;
			}
			return overres::ObjectWrap::Unwrap<T>(from.As<v8::Object>());
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<T> from) {
			return from->Wrap();
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
	class value_converter<std::shared_ptr<T>, typename std::enable_if<std::is_base_of<ObjectWrap, T>::value>::type> : public value_converter_base {
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
	class value_converter<std::shared_ptr<T>,typename std::enable_if<std::is_base_of<IStructuredObject,T>::value>::type> : public value_converter_base {
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
	class value_converter<std::shared_ptr<std::vector<T>>> : public value_converter_base {
	public:

		virtual std::shared_ptr<std::vector<T>> convert(v8::Local<v8::Value> from) {
			if (from->IsArray()) {
				auto arr = std::make_shared<std::vector<T>>();
				auto converter = std::make_shared<value_converter<T>>();
				auto fromArray = from.As<v8::Array>();
				for (uint32_t i = 0; i < fromArray->Length(); i++) {
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
			
			throw std::runtime_error("converted v8 value does not contain an array or buffer");
		}

		static void FreeBufferCallback(char *data, void *hint) {
			delete (std::shared_ptr<std::vector<T>> *) hint;
		}
		
		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::vector<T>> from) {
			if (std::is_same<T, uint8_t>::value) {
				if (from != nullptr) {
					//create a manual instance of shared_ptr to increment the ref counter manually, which will be deleted by FreeBufferCallback when Buffer is free'd
					auto copy_for_ref_inc = new std::shared_ptr<std::vector<T>>(from);

					auto v8buffer = Nan::NewBuffer((char*)&(*from)[0], from->size(), FreeBufferCallback, copy_for_ref_inc);
					return v8buffer.ToLocalChecked();
				}
				else {
					return Nan::NewBuffer(0).ToLocalChecked();
				}
			}

			auto v8array = Nan::New<v8::Array>();
			if (from != nullptr) {
				auto converter = std::make_shared<value_converter<T>>();
				for (size_t i = 0; i < from->size(); i++) {
					v8array->Set(i, converter->convert((*from)[i]));
				}
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
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
	template<typename T>
	class value_converter<std::shared_ptr<std::map<std::string, T>>> : public value_converter_base {
	public:

		virtual std::shared_ptr<std::map<std::string, T>> convert(v8::Local<v8::Value> from) {
			if (!from->IsMap()) {
				throw std::runtime_error("converted v8 value does not contain a v8::Map");
			}

			auto converter = std::make_shared<value_converter<T>>();

			auto map_value = std::make_shared<std::map<std::string, T>>();
			auto from_map = from.As<v8::Map>()->AsArray();
			assert((from_map->Length() % 2) == 0 && "v8::Map::AsArray returned length other than % 2");
			for (uint32_t i = 0; i < from_map->Length(); i+=2) {
				auto key = *Nan::Utf8String(from_map->Get(i));
				auto value = converter->convert(from_map->Get(i + 1));

				(*map_value)[key] = value;
			}

			return map_value;
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::map<std::string,T>> from) {
			auto converter = std::make_shared<value_converter<T>>();

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
#endif

	//map <K, V>
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
	template<typename K, typename T>
	class value_converter<std::shared_ptr<std::map<K, T>>> : public value_converter_base {
	public:

		virtual std::shared_ptr<std::map<K, T>> convert(v8::Local<v8::Value> from) {
			
			if (!from->IsMap()) {
				throw std::runtime_error("converted v8 value does not contain a v8::Map");
			}

			auto value_convert = std::make_shared<value_converter<T>>();
			auto key_convert = std::make_shared<value_converter<K>>();

			auto map_value = std::make_shared<std::map<std::string, T>>();
			auto from_map = from.As<v8::Map>()->AsArray();
			assert((from_map->Length() % 2) == 0 && "v8::Map::AsArray returned length other than % 2");
			for (auto i = 0; i < from_map->Length(); i += 2) {
				auto key = key_convert->convert(from_map->Get(i));
				auto value = value_convert->convert(from_map->Get(i + 1));

				(*map_value)[key] = value;
			}

			return map_value;
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::map<K,T>> from) {
			auto value_convert = std::make_shared<value_converter<T>>();
			auto key_convert = std::make_shared<value_converter<K>>();

			auto map_value = v8::Map::New(v8::Isolate::GetCurrent()); //Nan::New<v8::Map>();

			for (auto &&kv : *from) {
				map_value->Set(Nan::GetCurrentContext(),key_convert->convert(kv.first), value_convert->convert(kv.second));
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
#endif

	//set <T>
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
	template<typename T>
	class value_converter<std::shared_ptr<std::set<T>>> : public value_converter_base {
	public:

		virtual std::shared_ptr<std::set<T>> convert(v8::Local<v8::Value> from) {

			if (!from->IsSet()) {
				throw std::runtime_error("converted v8 value does not contain a v8::Set");
			}

			auto converter = std::make_shared<value_converter<T>>();

			auto set_value = std::make_shared<std::set<T>>();
			auto from_set = from.As<v8::Set>()->AsArray();
			for (uint32_t i = 0; i < from_set->Length(); i ++) {
				auto value = converter->convert(from_set->Get(i));

				set_value->insert(value);
			}

			return set_value;
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<std::set<T>> from) {
			auto converter = std::make_shared<value_converter<T>>();

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
#endif

	//string

	template<>
	class value_converter<std::string> : public value_converter_base {
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
	class value_converter<int> : public value_converter_base {
	public:

		virtual int convert(v8::Local<v8::Value> from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
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

	template<>
	class value_converter<unsigned int> : public value_converter_base {
	public:

		virtual unsigned int convert(v8::Local<v8::Value> from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
			return from->IntegerValue();
		}

		virtual v8::Local<v8::Value> convert(unsigned int from) {
			return Nan::New(from);
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<unsigned int> from) {
			return Nan::New(*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<unsigned int>>(from);
			return Nan::New(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<unsigned int>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};


	template<>
	class value_converter<uint64_t> : public value_converter_base {
	public:

		virtual uint64_t convert(v8::Local<v8::Value> from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
			return from->IntegerValue();
		}

		virtual v8::Local<v8::Value> convert(uint64_t from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
			return Nan::New((double)from);
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<uint64_t> from) {
			return Nan::New((double)*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<uint64_t>>(from);
			return Nan::New((double)from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<uint64_t>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	template<>
	class value_converter<int64_t> : public value_converter_base {
	public:

		virtual int64_t convert(v8::Local<v8::Value> from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
			return from->IntegerValue();
		}

		virtual v8::Local<v8::Value> convert(int64_t from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
			return Nan::New((double)from);
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<int64_t> from) {
			return Nan::New((double)*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<int64_t>>(from);
			return Nan::New((double)from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<int64_t>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};


	//ushort
	

	template<>
	class value_converter<ushort> : public value_converter_base {
	public:

		virtual ushort convert(v8::Local<v8::Value> from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
			return from->NumberValue();
		}

		virtual v8::Local<v8::Value> convert(ushort from) {
			return Nan::New(from);
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<ushort> from) {
			return Nan::New(*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<ushort>>(from);
			return Nan::New(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<ushort>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	//short

	template<>
	class value_converter<short> : public value_converter_base {
	public:

		virtual short convert(v8::Local<v8::Value> from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
			return from->NumberValue();
		}

		virtual v8::Local<v8::Value> convert(short from) {
			return Nan::New(from);
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<short> from) {
			return Nan::New(*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<short>>(from);
			return Nan::New(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<short>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};


	//float

	template<>
	class value_converter<float> : public value_converter_base {
	public:

		virtual double convert(v8::Local<v8::Value> from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
			return from->NumberValue();
		}

		virtual v8::Local<v8::Value> convert(float from) {
			return Nan::New(from);
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<float> from) {
			return Nan::New(*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<float>>(from);
			return Nan::New(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<float>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	template<>
	class value_converter<double> : public value_converter_base {
	public:

		virtual double convert(v8::Local<v8::Value> from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
			return from->NumberValue();
		}

		virtual v8::Local<v8::Value> convert(double from) {
			return Nan::New(from);
		}


		virtual v8::Local<v8::Value> convert(std::shared_ptr<double> from) {
			return Nan::New(*from);
		}

		virtual v8::Local<v8::Value> convert(std::shared_ptr<value_holder_base> from) {
			auto from_value = std::dynamic_pointer_cast<value_holder<double>>(from);
			return Nan::New(from_value->Value);
		}

		virtual std::shared_ptr<value_holder_base> read(v8::Local<v8::Value> val) {
			auto parsed_value = std::make_shared<value_holder<double>>();
			parsed_value->Value = convert(val);
			return parsed_value;
		}

	};

	//uint8_t / number

	template<>
	class value_converter<uint8_t> : public value_converter_base {
	public:

		virtual uint8_t convert(v8::Local<v8::Value> from) {
			//TODO: decide if value should be checked against std::numeric_limits<T>::max() and std::numeric_limits<T>::min() 
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
	class value_converter<bool> : public value_converter_base {
	public:

		virtual bool convert(v8::Local<v8::Value> from) {
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
	class value_converter<DateTime> : public value_converter_base {
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

}
#endif