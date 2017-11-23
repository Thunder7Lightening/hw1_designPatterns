#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>

using std::string;

class Struct: public Term {
public:
  Struct(Atom name): _name(name), _args() {}

  Struct(Atom name, std::vector<Term *> args): _name(name), _args(args) {}

  int arity(){ // return the number of args (terms)
    return _args.size();
  }

  Term * args(int index) {
    return _args[index];
  }

  Atom & name() {
    return _name;
  }

  // string symbol() const {
  //   string ret = _name.symbol() + "(";
  //   std::vector<Term *>::const_iterator it = _args.begin();
  //   for (; it != _args.end()-1; ++it)
  //     ret += (*it)->symbol()+", ";
  //   ret += (*it)->symbol()+")";
  //   return ret;
  // }
  virtual string symbol() const
	{
		string ret = _name.symbol() + "(";

    if(_args.size() > 0)
    {
      for(int i = 0; i < _args.size() - 1 ; i++)
      {
        ret += _args[i]->symbol() + ", ";
      }
      ret += _args[_args.size()-1]->symbol();
    }

    ret += ")";
		return ret;
	}

  string value() const {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+")";
    return ret;
  }
private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
