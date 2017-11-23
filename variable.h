#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <typeinfo>
#include "atom.h"
using std::string;

class Variable : public Term {
public:
  static bool isVariable(Term *term){ return typeid(Variable) == typeid(term); }
  Variable(string s):Term(s), _inst(0){}
  string value() const {
    if (_inst)
      return _inst->value();
    else
      return Term::value();
  }
  bool match( Term & term ){
    if (this == &term)
      return true;
    if(!_inst){
      _inst = &term ;
      return true;
    }
    return _inst->match(term);
  }
private:
  Term * _inst;
};

#endif
