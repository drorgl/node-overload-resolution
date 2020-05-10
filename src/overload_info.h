#ifndef _O_R_OVERLOAD_RESOLUTION_OVERLOAD_INFO_H_
#define _O_R_OVERLOAD_RESOLUTION_OVERLOAD_INFO_H_

#include <memory>
#include <string>
#include <nan.h>
#include "value_converter.h"
#include "value_converter_base.h"

/**
 * @brief overload function argument type info
 * 
 */
struct overload_info {
	/**
	 * @brief argument parameter name
	 * 
	 */
	std::string parameterName;
	/**
	 * @brief argument parameter type
	 * 
	 */
	std::string type;
	/**
	 * @brief argument parameter default v8 value
	 * either defaultValue, defaultSharedValue or value_converter should be used
	 * 
	 */
	Nan::Persistent<v8::Value, Nan::CopyablePersistentTraits<v8::Value>> defaultValue;
	/**
	 * @brief argument parameter default C++ value
	 * either defaultValue, defaultSharedValue or value_converter should be used
	 * 
	 */
	std::shared_ptr<void> defaultSharedValue;
	/**
	 * @brief argument parameter default value converter value
	 * either defaultValue, defaultSharedValue or value_converter should be used
	 * 
	 */
	std::shared_ptr< overres::value_converter_base> value_converter;

	/**
	 * @brief Construct a new overload info with argument parameter name and type
	 * 
	 * @param parameterName the argument parameter name
	 * @param type the type of the argument parameter
	 */
	overload_info(const std::string &&parameterName, const std::string &&type);

	/**
	 * @brief Construct a new overload info with argument parameter name, type and v8 default value
	 * 
	 * @param parameterName the argument parameter name
	 * @param type the type of the argument parameter
	 * @param defaultValue the v8 default value
	 */
	overload_info(const std::string &&parameterName, const std::string &&type, v8::Local<v8::Value> defaultValue);

	/**
	 * @brief Construct a new overload info with argument parameter name, type and int default value
	 * 
	 * @param parameterName the argument parameter name
	 * @param type the type of the argument parameter
	 * @param defaultValue the int default value
	 */
	overload_info(const std::string &&parameterName, const std::string &&type, const int defaultValue);

	/**
	 * @brief Construct a new overload info with argument parameter name, type and double default value
	 * 
	 * @param parameterName the argument parameter name
	 * @param type the type of the argument parameter
	 * @param defaultValue the double default value
	 */
	overload_info(const std::string &&parameterName, const std::string &&type, const double defaultValue);

	/**
	 * @brief Construct a new overload info with argument parameter name, type and bool default value
	 * 
	 * @param parameterName the argument parameter name
	 * @param type the type of the argument parameter
	 * @param defaultValue the bool default value
	 */
	overload_info(const std::string &&parameterName, const std::string &&type, const bool defaultValue);

	/**
	 * @brief Construct a new overload info with argument parameter name, type and string default value
	 * 
	 * @param parameterName the argument parameter name
	 * @param type the type of the argument parameter
	 * @param defaultValue the string default value
	 */
	overload_info(const std::string &&parameterName, const std::string &&type, const std::string &&defaultValue);
};

/**
 * @brief creates a param instance with name and type
 * 
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @return std::shared_ptr<overload_info> the overload function argument type info
 */
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName),std::move( type));
}

/**
 * @brief creates a param instance with name, type and v8 default value
 * 
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @param defaultValue the v8 default value
 * @return std::shared_ptr<overload_info> the overload function argument type info
 */
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, v8::Local<v8::Value> defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName), std::move(type), defaultValue);
}

/**
 * @brief creates a param instance with name, type and bool default value
 * 
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @param defaultValue the bool default value
 * @return std::shared_ptr<overload_info> the overload function argument type info
 */
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type,const bool defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName),std::move( type), defaultValue);
}

/**
 * @brief creates a param instance with name, type and int default value
 * 
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @param defaultValue the int default value
 * @return std::shared_ptr<overload_info> the overload function argument type info
 */
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type,const int defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName), std::move(type), defaultValue);
}


/**
 * @brief creates a param instance with name, type and double default value
 * 
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @param defaultValue the double default value
 * @return std::shared_ptr<overload_info> the overload function argument type info
 */
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, const double defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName), std::move(type), defaultValue);
}

/**
 * @brief creates a param instance with name, type and string default value
 * 
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @param defaultValue the string default value
 * @return std::shared_ptr<overload_info> the overload function argument type info
 */
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, const std::string &&defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	return std::make_shared<overload_info>(std::move(parameterName), std::move(type), std::move(defaultValue));
}

/**
 * @brief creates a param instance with name, v8 type and C++ type
 * 
 * @tparam T C++ type
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @return std::shared_ptr<overload_info> the overload function argument type info
 */
template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type) {
	assert(!type.empty() && "type cannot be empty" );
	auto value_converter = std::make_shared < overres::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(std::move(parameterName), std::move(type));
	oi->value_converter = value_converter;

	return oi;
}

/**
 * @brief creates a param instance with name, v8 type and C++ type
 * 
 * @tparam T C++ type
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @param defaultValue the C++ object default value
 * @return std::shared_ptr<overload_info> the overload function argument type info
 */
template<typename T, typename std::enable_if<!std::is_convertible<T, v8::Local<v8::Value>>::value>::type* = nullptr>
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, T defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	auto value_converter = std::make_shared < overres::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(std::move(parameterName),std::move( type), value_converter->convert(defaultValue));
	oi->value_converter = value_converter;

	return oi;
}

/**
 * @brief creates a param instance with name, v8 type and C++ type
 * 
 * @tparam T C++ type
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @param defaultValue the C++ object default value
 * @return std::shared_ptr<overload_info> the overload function argument type info
 */
template<typename T, typename TREF = typename std::remove_reference<T>::type>
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, std::shared_ptr<TREF> defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	auto value_converter = std::make_shared < overres::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(std::move(parameterName),std::move( type), value_converter->convert(defaultValue));
	oi->value_converter = value_converter;
	
	oi->defaultSharedValue = defaultValue;

	return oi;
}

/**
 * @brief creates a param instance with name, v8 type and C++ type
 * 
 * @tparam T C++ type
 * @param parameterName the argument parameter name
 * @param type the argument type
 * @param defaultValue the v8 default value
 * @return std::shared_ptr<overload_info> 
 */
template<typename T>
inline std::shared_ptr<overload_info> make_param(const std::string &&parameterName, const std::string &&type, v8::Local<v8::Value> defaultValue) {
	assert(!type.empty() && "type cannot be empty");
	auto value_converter = std::make_shared < overres::value_converter<T>>();
	auto oi = std::make_shared<overload_info>(std::move(parameterName), std::move(type), value_converter->convert(defaultValue));
	oi->value_converter = value_converter;

	return oi;
}

#endif