#ifndef SIMPLEOBJECT_H
#define SIMPLEOBJECT_H

#include <string>
using std::string;

class SimpleObject
{
	string _value;
	string _symbol;

protected:
	void setValue(string v) { _value = v; }

public:
	SimpleObject(string s):_symbol(s),_value(s){}
	string value() const { return _value; };
	string symbol() const { return _symbol; }
	virtual bool match(SimpleObject *simpleObject) = 0;
};

#endif // !SIMPLEOBJECT_H
