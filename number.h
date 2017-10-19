#ifndef NUMBER_H
#define NUMBER_H

#include <typeinfo>
#include <string>
#include "constant.h"

using std::string;
using std::to_string;

class Number : public Constant
{
	template<typename Type>
	static string convertValueToString(Type v)
	{
		string ret = to_string(v);
		if(typeid(v) == typeid(double))
		{
			ret.erase (ret.find_last_not_of('0') + 1, string::npos);
		}
		return ret;
	}

public:
	template<typename Type>
	Number(Type v) : Constant(convertValueToString(v)){}
};

#endif // !NUMBER_H