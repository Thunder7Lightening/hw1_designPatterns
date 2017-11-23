#ifndef NODE_H
#define NODE_H

#include "global.h"
#include "atom.h"

class Node
{
public:
  int payload;
  Term *term;
  Node *left;
  Node *right;

  Node(int payload, Term *term = nullptr)
    : payload(payload), term(term), left(nullptr), right(nullptr){}

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
