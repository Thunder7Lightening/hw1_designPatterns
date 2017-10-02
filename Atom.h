#ifndef ATOM_H
#define ATOM_H

#include "Constant.h"
#include "Number.h"
#include <string>
using std::string;

class Atom : public Constant
{

public:
	Atom (string s):Constant(s){}
};

#endif
