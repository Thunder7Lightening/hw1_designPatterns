#ifndef NUMBER_H
#define NUMBER_H

#include "constant.h"
#include "atom.h"
#include "variable.h"
#include <string>
using std::string;

class Number : public Constant
{
	string convertValueFromIntToString(int v){ return std::to_string(v); }
public:
	Number(int v):Constant(convertValueFromIntToString(v)){}
	Number(string s):Constant(s){}
};

#endif
