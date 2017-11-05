#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "variable.h"

#include <vector>
using std::vector;

class List : public Term
{
public:
  static bool isList(Term *term) { return dynamic_cast<List *>(term); }

  List(): _elements() {}

  List(vector<Term *> const & elements):_elements(elements){}

  List(const List *l)
  {
    for(Term *term : l->_elements)
			_elements.push_back(term);
		_elements.erase(_elements.begin());
  }

  Term * head() const
  {
    if(_elements.empty())
      throw string("Accessing head in an empty list");
    else
      return _elements[0];
  }

  List * tail() const
  {
    if(_elements.empty())
      throw string("Accessing tail in an empty list");
    else
      return new List(this); // clone this to newList, meanwhile remove first item in newList; return newList;
  }

  virtual string symbol() const
  {
    string ret = "[";

  	if(_elements.size() > 0)
  	{
  		for(int i = 0; i < _elements.size() - 1 ; i++)
  			ret += _elements[i]->symbol() + ", ";
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
    			ret += _elements[i]->value() + ", ";
    		ret += _elements[_elements.size() - 1]->value();
    	}

    	ret += "]";
    	return ret;
  }

private:
  vector<Term *> _elements;

private:
  vector<Term *> elements()
  {
    return _elements;
  }

  Term *elements(int index)
  {
    return _elements[index];
  }
};

#endif
