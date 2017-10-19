#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include "term.h"
#include "constant.h"
#include "atom.h"

using std::vector;

class Struct : public Term
{
	Atom _name;
	vector<Term *> _args;
public:
	static bool isStruct(Term *term) { return dynamic_cast<Struct *>(term); }

	Struct(Atom const &name, vector<Term *> args):_name(name), _args(args){}

	Atom &name()
	{
		return _name;
	}

	Term *args(int index) 
	{
		return _args[index];
	}

	virtual string symbol() const 
	{ 
		string ret = _name.symbol() + "(";
		for(int i = 0; i < _args.size() - 1 ; i++)
		{
			ret += _args[i]->symbol() + ", ";
		}
		ret += _args[_args.size()-1]->symbol() + ")";
		return ret;
	}

	virtual string value()
	{
		string ret = _name.value() + "(";
		for(int i = 0; i < _args.size() - 1 ; i++)
		{
			ret += _args[i]->value() + ", ";
		}
		ret += _args[_args.size()-1]->value() + ")";
		return ret;
	}

	virtual bool match(Term *term)
	{
		bool ret = true;
		if(Constant::isConstant(term) || Struct::isStruct(term))
		{
			ret = (this->value() == term->value());
		}
		else // term is variable
		{
			ret = term->match(this);
		}
		return ret;
	}
};

#endif // !STRUCT_H