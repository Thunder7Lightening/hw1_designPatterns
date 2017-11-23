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
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
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
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  // TODO
  void replaceVariableArgsInTermIfAlreadyExistedIn_terms(Struct *structTerm)
  {
    Struct *argStructTerm;
    Variable *argVariableTerm;
    Term *oldTerm;

    for(int i = 0; i < structTerm->arity(); i++)
    {
      if(argStructTerm = dynamic_cast<Struct *>(structTerm->args(i)))
      {
        replaceVariableArgsInTermIfAlreadyExistedIn_terms(argStructTerm);
      }
      else if(argVariableTerm = dynamic_cast<Variable *>(structTerm->args(i)))
      {
        if(oldTerm = existTermIn_terms(argVariableTerm))
        {
          structTerm->_args[i] = oldTerm;
        }
      }
    }
  }

  // TODO
  Term *existTermIn_terms(Term *term)
  {
    Struct *structTerm;

    if(structTerm = dynamic_cast<Struct *>(term))
    {
      // TODO
      replaceVariableArgsInTermIfAlreadyExistedIn_terms(structTerm);
    }

    for(int i = _terms.size() - 1; i >= 0; i--)
    {
      // 檢查看看_terms裡面是否曾出現term
      if(term->symbol() == _terms[i]->symbol())
        return _terms[i];

      // TODO check is term already existed in structure args
      if(structTerm = dynamic_cast<Struct *>(_terms[i]))
      {
        // TODO 若_terms[i]為Struct，找args裡面是否曾出現term
        for(int i = 0; i < structTerm->arity(); i++)
        {
          if(term->symbol() == structTerm->args(i)->symbol())
            return structTerm->args(i);
        }
      }
    }

    return nullptr;
  }

  // TODO if term has already existed in _terms then points to the existed term
  Node *addTermTo_termsAndReturnTermNode(Term *term)
  {
    Term *oldTerm;
    if((oldTerm = existTermIn_terms(term)) == nullptr)
    {
      _terms.push_back(term);
      return new Node(TERM, term);
    }
    else
    {
      _terms.push_back(oldTerm);
      return new Node(TERM, oldTerm);
    }
  }

  void matching()
  {
    if(_currentToken == ';')
    {
      Term* term = createTerm();
      if(term!=nullptr)
      {
        // Node *termNode1 = addTermTo_termsAndReturnTermNode(term);
        _terms.push_back(term);
        Node *termNode1 = new Node(TERM, term);

        if((_currentToken = _scanner.nextToken()) == '=')
        {
          term = createTerm();
          // Node *termNode2 = addTermTo_termsAndReturnTermNode(term);
          _terms.push_back(term);
          Node *termNode2 = new Node(TERM, term);

          Node *operatorNode = new Node(EQUALITY);
          operatorNode->left = termNode1;
          operatorNode->right = termNode2;

          _et = operatorNode;
        }
      }
    }
    else
    {
      Term* term = createTerm();
      if(term!=nullptr)
      {
        Node *termNode1 = addTermTo_termsAndReturnTermNode(term);

        if((_currentToken = _scanner.nextToken()) == '=')
        {
          term = createTerm();
          Node *termNode2 = addTermTo_termsAndReturnTermNode(term);

          Node *operatorNode = new Node(EQUALITY);
          operatorNode->left = termNode1;
          operatorNode->right = termNode2;

          _et = operatorNode;
        }
      }
    }
  }

  void matchings()
  {
    this->matching();
    _scanner.skipLeadingWhiteSpace();
    if(_scanner.currentChar() != '.') // _currentToken != '.'
    {
      _currentToken = _scanner.nextToken(); // eat up ',' | ';'

      Node *operatorNode;
      switch(_currentToken)
      {
        case ',':
          operatorNode = new Node(COMMA);
          break;
        case ';':
          operatorNode = new Node(SEMICOLON);
          break;
      }
      operatorNode->left = _et;
      this->matchings();
      operatorNode->right = _et;
      _et = operatorNode;
    }
  }

  Node *expressionTree()
  {
    return _et;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

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

  Node *_et;
  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
};
#endif
