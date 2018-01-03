#ifndef EXP_H
#define EXP_H

#include "atom.h"

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getEvaluateString() {return "";}
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    return _left->match(*_right);
  }
  string getEvaluateString(){
    return _left->symbol() + " = " + _right->value() ;
  }
  
private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

  string getEvaluateString(){
    return (_left->getEvaluateString() + ", "+  _right->getEvaluateString());
  }

private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

private:
  Exp * _left;
  Exp * _right;
};
#endif
