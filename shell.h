#ifndef SHELL_H
#define SHELL_H

#include "exp.h"
#include "parser.h"
#include <string>
using namespace std;

class Shell
{
private:
  string _result;

public:
  string getResult() { return _result; }

  void buildResult(Exp* root)
  {
    if(root->evaluate())
      _result = root->getExpression();
    else
      _result = "false";
    _result += ".";
  }

};

#endif
