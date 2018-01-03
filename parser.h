#ifndef PARSER_H
#define PARSER_H

#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include "iterator.h"
#include <stack>

using std::stack;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' )
        return structure();
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void buildExpression(){
    // createTerm();
    disjunctionMatch();
    restDisjunctionMatch();
    if (createTerm() != nullptr || _currentToken != '.')
      throw string("Missing token '.'");
  }

  void restDisjunctionMatch() {
    if (_scanner.currentChar() == ';') {
      createTerm();
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch() {
    if (_scanner.currentChar() == ',') {
      createTerm();
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
    if(_scanner.currentChar() == '.'){
      throw string("Unexpected ',' before '.'");
    }

    Term * left = createTerm();
    doWeNeedToLinkVarToVarFromStorage(left);

    if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
      doWeNeedToLinkVarToVarFromStorage(right);
      _expStack.push(new MatchExp(left, right));
    }else if(_currentToken == ';'){
      throw string("Unexpected ';' before '.'");
    }else if(_currentToken == ','){
      throw string("Unexpected ',' before '.'");
    }else{
      throw string("X does never get assignment");
    }
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  FRIEND_TEST(ParserTest, createTerms);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  bool isVarExistInStorage(Variable* var)
  {
    // return linkToVarExistInStorage(var);
    for(int i = 0; i < _varStorage.size(); i++)
    {
      if(_varStorage[i]->symbol() == var->symbol())
        return true;
    }
    return false;
  }

  Variable* linkToVarExistInStorage(Variable* var)
  {
    for(int i = 0; i < _varStorage.size(); i++)
    {
      if(_varStorage[i]->symbol() == var->symbol())
        return _varStorage[i];
    }
    return nullptr;
  }

  void doWeNeedToLinkVarToVarFromStorage(Term * &term)
  {
    // process pure var
    checkAndLinkVar(term);

    // process var in list
    List* list = dynamic_cast<List*>(term);
    if(list)
    {
      Iterator* it = list->createIterator();
      for(it->first(); !it->isDone(); it->next())
      {
        Term* item = it->currentItem();
        checkAndLinkVar(item);
      }
    }
  }

  void checkAndLinkVar(Term * &term)
  {
    Variable* var = dynamic_cast<Variable*>(term);
    if(var)
    {
      if(isVarExistInStorage(var))
        term = linkToVarExistInStorage(var);
      else
        _varStorage.push_back(var);
      return;
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  //MatchExp* _root;
  stack<Exp*> _expStack;
  vector<Variable*> _varStorage;
};
#endif
