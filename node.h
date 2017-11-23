#ifndef NODE_H
#define NODE_H

#include "global.h"
#include "atom.h"

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node
{
public:
  Operators payload;
  Term *term;
  Node *left;
  Node *right;

  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l = nullptr, Node *r = nullptr):payload(op), term(t), left(l), right(r) {}

  // Node(Operators payload, Term *term = nullptr)
  //   : payload(payload), term(term), left(nullptr), right(nullptr){}

  bool evaluate()
  {
    Term *leftNodeTerm = left->term;
    Term *rightNodeTerm = right->term;

    if(left->payload == TERM && right->payload == TERM)
      return leftNodeTerm->match(*rightNodeTerm);
    else
      return left->evaluate() && right->evaluate();
  }
};

#endif
