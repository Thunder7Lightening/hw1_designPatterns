#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "constant.h"

using std::string;

class Atom : public Constant
{
	
public:
	Atom(string s) : Constant(s){}
};

#endif // !ATOM_H