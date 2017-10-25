#ifndef SIMPLEOBJECT_H
#define SIMPLEOBJECT_H

#include <string>
#include "term.h"

using std::string;

class SimpleObject : public Term
{
	const string _symbol;
public:
	static bool isSimpleObject(Term *term) { return dynamic_cast<SimpleObject *>(term); }
	SimpleObject(string s) : _symbol(s){}
	virtual string symbol() const { return _symbol; }
	virtual string value() = 0;
	virtual bool match(Term *term) = 0;
	virtual bool match(Term &term) = 0;
};

#endif // !SIMPLEOBJECT_H
