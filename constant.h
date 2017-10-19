#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>
#include "term.h"
#include "simpleObject.h"

using std::string;

class Constant : public SimpleObject
{

public:
	static bool isConstant(Term *term) { return dynamic_cast<Constant *>(term); }

	Constant(string s) : SimpleObject(s){}

	virtual string value() { return this->symbol(); }

	virtual bool match(Term *term)
	{ 
		bool ret = true;
		if(Constant::isConstant(term))
		{
			ret = (this->value() == term->value());
		}
		else
		{
			ret = term->match(this);
		}
		return ret;
	}
};

#endif // !CONSTANT_H