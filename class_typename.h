#ifndef _O_R_CLASS_TYPENAME_H_
#define _O_R_CLASS_TYPENAME_H_

template <typename T>
class Class_TypeName {
public:
	static const char *name; 
};

#define DECLARE_CLASS_TYPENAME(x) template<> const char *Class_TypeName<x>::name = #x;


#endif