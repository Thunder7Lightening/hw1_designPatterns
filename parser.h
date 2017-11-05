#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stack>
using std::string;
using std::stack;

#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}

  Term* createTerm(){
    Term *term;
    int tokenTypeOrChar = _scanner.nextToken();

    if(_scanner.isBufferIllegal())
    {
      throw string("unexpected token");
    }

    // ignore token ','  when scanner's buffer has over 1 term.
    if(tokenTypeOrChar == ',')
    {
      tokenTypeOrChar = _scanner.nextToken();
    }

    if(tokenTypeOrChar == VAR){
      term = new Variable(symtable[_scanner.tokenIndex()].symbolName);
    }else if(tokenTypeOrChar == NUMBER){
      term = new Number(_scanner.tokenIndex());
    }else if(tokenTypeOrChar == ATOM || tokenTypeOrChar == ATOMSC){ // create Atom or Struct
        Atom* atom = new Atom(symtable[_scanner.tokenIndex()].symbolName);
        // if(_scanner.currentChar() == '(' ) {
        //   _scanner.nextToken(); // ignore '('
        //   vector<Term*> terms = getArgs();
        //   if(_currentToken == ')')
        //     term = new Struct(*atom, terms);
        //   term = new Struct(*atom, terms);
        // }
        if(_scanner.nextToken() == '(' ) {
          vector<Term*> terms = getArgs();
          term = new Struct(*atom, terms);
        }
        else
          term = atom;
    }else if(tokenTypeOrChar == '['){ // create List
      vector<Term *> listArgs = getListArgs();
      term = new List(listArgs);
    }else
      term = nullptr;
    return term;
  }

  vector<Term *> getListArgs()
  {
    vector<Term *> listArgs;

    Term* term = createTerm();
    if(term)
    {
      listArgs.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',')
      {
        listArgs.push_back(createTerm());
      }
    }

    return listArgs;
  }

  vector<Term*> getArgs()
  {
    vector<Term*> args;

    Term* term = createTerm();
    if(term)
    {
      args.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',')
      {
        args.push_back(createTerm());
      }
    }

    return args;
  }

private:
  Scanner _scanner;
  int _currentToken;
};

#endif
