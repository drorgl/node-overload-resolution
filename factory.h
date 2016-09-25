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
	void register_type(const char * name)
	{
		static_assert(std::is_base_of<T, TDerived>::value, "Factory::register_type doesn't accept this type because doesn't derive from base class");
		_createFuncs[name] = &createFunc<TDerived>;
	}

	T* create(const char * name) {
		typename std::map<const char *, PCreateFunc>::const_iterator it = _createFuncs.find(name);
		if (it != _createFuncs.end()) {
			return it.value()();
		}
		return nullptr;
	}

	//TODO: implement
	std::vector<std::pair<const char *, T>> all() {
		std::vector<std::pair<const char *, T>> v;
		/*for (std::map<const char *, PCreateFunc>::iterator it = _createFuncs.begin(); it != _createFuncs.end(); ++it) {
			v.push_back(std::pair<const char *, T>(it->first(), it->second->value()()));
		}*/
		return v;
	}

private:
	template <typename TDerived>
	static T* createFunc()
	{
		return new TDerived();
	}

	typedef T* (*PCreateFunc)();
	std::map<const char *, PCreateFunc> _createFuncs;
};


#endif // FACTORY_H