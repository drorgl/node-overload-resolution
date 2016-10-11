//https://stackoverflow.com/questions/5120768/how-to-implement-the-factory-method-pattern-in-c-correctly
#ifndef _ALVISION_FACTORY_H_
#define _ALVISION_FACTORY_H_

#include <map>
#include <vector>


template <typename T>
class Factory
{
public:
	template <typename TDerived>
	void register_type(std::string name)
	{
		static_assert(std::is_base_of<T, TDerived>::value, "Factory::register_type doesn't accept this type because doesn't derive from base class");
		_createFuncs[name] = &createFunc<TDerived>;
	}

	bool has_type(std::string name) {
		return (_createFuncs .find(name) != std::end(_createFuncs));
	}

	std::shared_ptr<T> create(std::string name) {
		typename std::map<std::string, PCreateFunc>::const_iterator it = _createFuncs.find(name);
		if (it != _createFuncs.end()) {
			return it.value()();
		}
		return nullptr;
	}

	std::vector<std::pair<std::string, std::shared_ptr<T>>> all() {
		std::vector<std::pair<std::string, std::shared_ptr<T>>> v;
		for (std::map<std::string, PCreateFunc>::const_iterator it =std::begin(_createFuncs); it != std::end( _createFuncs); ++it) {

			v.push_back(std::pair<std::string, std::shared_ptr<T>>(it->first, it->second()));

		}
		return v;
	}

private:
	template <typename TDerived>
	static std::shared_ptr<T> createFunc()
	{
		return std::make_shared<TDerived>();
	}

	typedef std::shared_ptr<T> (*PCreateFunc)();


	std::map<std::string, PCreateFunc> _createFuncs;
};


#endif // FACTORY_H