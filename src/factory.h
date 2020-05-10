#ifndef _ALVISION_FACTORY_H_
#define _ALVISION_FACTORY_H_

#include <map>
#include <vector>

/**
 * @brief type factory
 * [Reference](https://stackoverflow.com/questions/5120768/how-to-implement-the-factory-method-pattern-in-c-correctly)
 * 
 * @tparam T base class of all types in the factory
 */
template <typename T>
class Factory
{
public:
	/**
	 * @brief registers type
	 * 
	 * @tparam TDerived derived class from T
	 * @param name name of TDerived
	 */
	template <typename TDerived>
	void register_type(const std::string &&name)
	{
		static_assert(std::is_base_of<T, TDerived>::value, "Factory::register_type doesn't accept this type because doesn't derive from base class");
		_createFuncs[name] = &createFunc<TDerived>;
	}

	/**
	 * @brief checks if type name exists in factory
	 * 
	 * @param name name of type to check
	 * @return true if the type is registered
	 * @return false if the type is not registered
	 */
	bool has_type(const std::string &name) {
		return (_createFuncs .find(name) != std::end(_createFuncs));
	}

	/**
	 * @brief create an instance from type name
	 * 
	 * @param name name of type to instantiate
	 * @return std::shared_ptr<T> instance of created type or nullptr if it does not exist
	 */
	std::shared_ptr<T> create(const std::string &&name) {
		typename std::map<std::string, PCreateFunc>::const_iterator it = _createFuncs.find(name);
		if (it != _createFuncs.end()) {
			return it.value()();
		}
		return nullptr;
	}

	/**
	 * @brief creates all types in the factory
	 * 
	 * @return std::vector<std::pair<std::string, std::shared_ptr<T>>> a vector of types and a new instance
	 */
	std::vector<std::pair<std::string, std::shared_ptr<T>>> all() {
		std::vector<std::pair<std::string, std::shared_ptr<T>>> v;
		for (auto it =std::begin(_createFuncs); it != std::end( _createFuncs); ++it) {

			v.push_back(std::pair<std::string, std::shared_ptr<T>>(it->first, it->second()));

		}
		return v;
	}

private:
	/**
	 * @brief Create a TDerived object
	 * 
	 * @tparam TDerived base class derived class to create
	 * @return std::shared_ptr<T> new instance of TDerived casted to T
	 */
	template <typename TDerived>
	static std::shared_ptr<T> createFunc()
	{
		return std::make_shared<TDerived>();
	}

	typedef std::shared_ptr<T> (*PCreateFunc)();


	std::map<std::string, PCreateFunc> _createFuncs;
};


#endif // FACTORY_H