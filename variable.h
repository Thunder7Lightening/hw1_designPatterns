#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <cctype>
#include <vector>
#include "term.h"
#include "simpleObject.h"

using std::string;
using std::isupper;
using std::vector;

class Variable : public SimpleObject
{
	Term *_instance; // �ĥ�link list�覡���s�A���DVariable�������@�w�O�\�b�̫᭱ (ex: X > Z > Y > 1)

	Term *instance() { return _instance; }

	void instantiatedTo(Term *term)
	{
		Variable *lastVar = dynamic_cast<Variable *>(this->lastVariableInstance());
		lastVar->_instance = term;
		_instance = term;
	}

	bool isInstantiated() const { return _instance != NULL; }

public:
	static bool isVariable(Term *term) { return dynamic_cast<Variable *>(term); }
	static bool isVariable(string arg) { return arg.size() && isupper(arg[0]); }

	Variable(string s)
		: SimpleObject(s), _instance(NULL){}

	virtual string value()
	{
		string ret = this->symbol();
		if(this->isInstantiated())
		{
			ret = this->instance()->value();
			ret = (Variable::isVariable(ret)) ? this->symbol() : ret;
		}
		return ret;
	}

	Term *lastVariableInstance() // means this value, but in Term * form.
	{
		Term *ret = this;
		if(this->isInstantiated() && Variable::isVariable(this->instance()))
		{
			ret = this->instance();
			Variable *var =  dynamic_cast<Variable *>(ret);
			if(var)
			{
				ret = var->lastVariableInstance();
			}
		}
		return ret;
	}

	Term *lastNonVariableInstance() // means this value, but in Term * form.
	{
		Term *ret = this;
		if(this->isInstantiated())
		{
			ret = this->instance();
			Variable *var =  dynamic_cast<Variable *>(ret);
			if(var)
			{
				ret = var->lastNonVariableInstance();
			}
		}
		return ret;
	}

	// TODO
	virtual bool match(Term *term)
	{
		bool ret = true;

		if(!Variable::isVariable(term)) // term is constant or struct.
		{
			if(this->isThereNonVariableValue())
			{
				ret = this->value() == term->value();
			}
			else
			{
				this->instantiatedTo(term);
				ret = true;
			}
		}
		else // term is var.
		{
			if(this->symbol() != term->symbol())
			{
				Variable *termVar = dynamic_cast<Variable *>(term);
				if(this->isThereNonVariableValue() && termVar->isThereNonVariableValue())
				{
					ret = this->value() == termVar->value();
				}
				else if(this->isThereNonVariableValue())
				{
					termVar->instantiatedTo(this->lastNonVariableInstance());
					ret = true;
				}
				else if(termVar->isThereNonVariableValue())
				{
					this->instantiatedTo(termVar->lastNonVariableInstance());
					ret = true;
				}
				else // both dont have real value(non-var value)
				{
					this->instantiatedTo(termVar);
					ret = true;
				}
			}
			else
			{
				ret = true;
			}
		}

		return ret;
	}

	virtual bool match(Term &term)
	{
		return this->match(&term);
	}

	bool isThereNonVariableValue()
	{
		return this->value() != this->symbol();
	}
};

#endif // !VARIABLE_H
