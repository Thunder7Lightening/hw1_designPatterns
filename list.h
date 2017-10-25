#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "variable.h"

#include <exception>
#include <vector>
using std::exception;
using std::vector;

struct HeadException : exception
{
  const char* what() const noexcept {return "Accessing head in an empty list";}
};

struct TailException : exception
{
  const char* what() const noexcept {return "Accessing tail in an empty list";}
};

class List : public Term
{
  vector<Term *> _elements;

  bool matchEachElementInList(List *termList)
  {
    if(this->_elements.size() != termList->elements().size())
    {
      return false;
    }
    else
    {
      for(int i = 0; i < this->elements().size(); i++)
      {
        if(!this->elements(i)->match(termList->elements(i)))
        {
          return false;
        }
      }
      return true;
    }
  }

public:
  static bool isList(Term *term) { return dynamic_cast<List *>(term); }

  bool isThereVariable(Variable *termVariable)
  {
    for(int i = 0 ; i < this->elements().size(); i++)
    {
      if(this->elements(i)->value() == termVariable->value())
      {
        return true;
      }
    }
    return false;
  }

  vector<Term *> elements()
  {
    return _elements;
  }

  Term *elements(int index)
  {
    return _elements[index];
  }

  virtual string symbol() const
  {
    string ret = "[";

  	if(_elements.size() > 0)
  	{
  		for(int i = 0; i < _elements.size() - 1 ; i++)
  		{
  			ret += _elements[i]->symbol() + ", ";
  		}
  		ret += _elements[_elements.size() - 1]->symbol();
  	}

  	ret += "]";
  	return ret;
  }

  virtual string value()
  {
      string ret = "[";

    	if(_elements.size() > 0)
    	{
    		for(int i = 0; i < _elements.size() - 1 ; i++)
    		{
    			ret += _elements[i]->value() + ", ";
    		}
    		ret += _elements[_elements.size() - 1]->value();
    	}

    	ret += "]";
    	return ret;
  }

  // TODO
  virtual bool match(Term *term)
  {
    if(!List::isList(term) && !Variable::isVariable(term))
  		return false;
  	else if(Variable::isVariable(term))
    {
  		if(this->isThereVariable(dynamic_cast<Variable *>(term))) // this contains term already(means same individual variable)
  			return false;
  		else
  			return term->match(this);
    }
  	else // term is List
  		return this->matchEachElementInList(dynamic_cast<List *>(term)); // is each element in this matchable;
  }

  virtual bool match(Term &term)
  {
    return this->match(&term);
  }

public:
  List(): _elements() {}

  List(vector<Term *> const & elements):_elements(elements){}

  // TODO
  List(const List *l)
  {
    for(Term *term : l->_elements)
		{
			_elements.push_back(term);
		}

		_elements.erase(_elements.begin());
  }

  Term * head() const
  {
    if(_elements.empty())
    {
      throw new HeadException();
    }
    else
    {
      return _elements[0];
    }
  }

  // TODO change first-line instruction of tail()
  List * tail() const
  {
    if(_elements.empty())
    {
      throw new TailException();
    }
    else
    {
      /*
        clone this to newList, meanwhile remove first item in newList;
        return newList;
      */
      List *ret = new List(this);
      return ret;
    }
  }
};

#endif
