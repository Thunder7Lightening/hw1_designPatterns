#ifndef NUMBER_H
#define NUMBER_H

#include "Constant.h"
#include "Atom.h"
#include "Variable.h"
#include <string>
using std::string;

class Number : public Constant
{

public:
	Number(string s):Constant(s){}
};

#endif
