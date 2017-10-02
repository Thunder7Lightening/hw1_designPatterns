#ifndef NUMBER_H
#define NUMBER_H

#include "constant.h"
#include "atom.h"
#include "variable.h"
#include <string>
using std::string;

class Number : public Constant
{

public:
	Number(string s):Constant(s){}
};

#endif
