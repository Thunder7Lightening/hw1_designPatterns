#ifndef VARIABLE_H
#define VARIABLE_H

#include "simpleObject.h"
#include <typeinfo>
#include <string>
using std::string;

class Variable : public SimpleObject
{
	bool _firstAssign;
	Variable *_anotherVariableWithSameValue;

	bool isVariable(SimpleObject *simpleObject)
	{
		return typeid(*simpleObject) == typeid(Variable);
	}

	void setAnotherVariableWithSameValue(Variable *anotherVariable)
	{
		_anotherVariableWithSameValue = anotherVariable;
	}

	bool doesExistAnotherVariableWithSameValue() const
	{
		return _anotherVariableWithSameValue != NULL;
	}

public:
	Variable(string s):SimpleObject(s), _firstAssign(true), _anotherVariableWithSameValue(NULL){}

	bool match(SimpleObject *simpleObject)
	{
		bool ret = true;

		if(isVariable(simpleObject))
		{
			setAnotherVariableWithSameValue(dynamic_cast<Variable *>(simpleObject));
			_anotherVariableWithSameValue->setAnotherVariableWithSameValue(this);

			// this value has changed, so this another variable has to change value too
			if(this->value() != this->symbol())
			{
				_anotherVariableWithSameValue->setValue(this->value());
			}

			// another variable's value has changed, so this has to change value too
			if(_anotherVariableWithSameValue->value() != _anotherVariableWithSameValue->symbol())
			{
				this->setValue(_anotherVariableWithSameValue->value());
			}
		}
		else
		{
			if(_firstAssign)
				_firstAssign = false;
			else if(this->value() != simpleObject->value())
				ret = false;

			// set value to all var.
			this->setValue(simpleObject->value());
			if(doesExistAnotherVariableWithSameValue())
				_anotherVariableWithSameValue->setValue(simpleObject->value());
		}

		return ret;
	}

	bool match(SimpleObject &simpleObject)
	{
		return this->match(&simpleObject);
	}
};

#endif
