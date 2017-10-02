#ifndef CONSTANT_H
#define CONSTANT_H

#include "simpleObject.h"
#include "variable.h"
#include <typeinfo>
#include <string>
using std::string;

class Constant : public SimpleObject
{
	bool isVariable(SimpleObject *simpleObject)
	{
		return typeid(*simpleObject) == typeid(Variable);
	}

public:
	Constant(string s):SimpleObject(s){}

	bool match(SimpleObject *simpleObject)
	{
		bool ret;
		if(isVariable(simpleObject))
			ret = simpleObject->match(this);
		else
			ret = this->value() == simpleObject->value();
		return ret;
	}
};

#endif // !CONSTANT_H
