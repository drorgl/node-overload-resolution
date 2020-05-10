#ifndef _O_R_CLASS_TYPENAME_H_
#define _O_R_CLASS_TYPENAME_H_

#include <iostream>
#include <string>

namespace overres {
	namespace internal{

#ifdef _MSC_VER
#define FUNC_MACRO __FUNCTION__
		static const char FRONT[] = "GetTypeNameHelper<";
		static const char BACK[] = ">::GetTypeName";
#else
#define FUNC_MACRO __PRETTY_FUNCTION__
		static const char FRONT[] = "T = ";
		static const char BACK[] = ";";
		static const char BACK_ALT[] = "]";
#endif

		template <typename T>
		struct GetTypeNameHelper
		{
			static const std::string GetTypeName(void)
			{

				std::string func_str = FUNC_MACRO;
				size_t front_pos = func_str.find(FRONT) + sizeof(FRONT) - 1;
				size_t back_pos = func_str.find(BACK);

#ifndef _MSC_VER
				if (back_pos == std::string::npos)
					back_pos = func_str.find(BACK_ALT);
#endif

				if (front_pos == std::string::npos || back_pos == std::string::npos)
					return "GetTypeNameError";

				return func_str.substr(front_pos, back_pos - front_pos);
			}
		};
	}
}

/**
 * @brief Get the Type Name for T
 * 
 * @tparam T C++ type to find its name
 * @return const std::string 
 */
template <typename T>
const std::string GetTypeName(void)
{
	return overres::internal::GetTypeNameHelper<T>::GetTypeName();
}


#endif