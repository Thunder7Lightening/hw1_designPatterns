#ifndef EXP_H
#define EXP_H

#include "atom.h"

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual Exp* left() = 0;
  virtual Exp* right() = 0;
  virtual string getExpression() = 0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){}

  bool evaluate(){
    return _left->match(*_right);
  }

  Exp* left() { return nullptr; }
  Exp* right() { return nullptr; }

  string getExpression()
  {
    string ret = "";
    if(_left->symbol() == _right->value())
      ret = "true";
    else
      ret = _left->symbol() + " = " + _right->value();
    return ret;
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {}

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

  Exp* left() { return _left; }
  Exp* right() { return _right; }

  string getExpression()
  {
    return  _left->getExpression() + ", " + _right->getExpression();
  }

private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {}

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

  Exp* left() { return _left; }
  Exp* right() { return _right; }

  string getExpression()
  {
    return _left->getExpression() + "; " + _right->getExpression();
  }

private:
  Exp * _left;
  Exp * _right;
};
#endif
