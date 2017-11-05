#ifndef GLOBAL_H
#define GLOBAL_H

#include <algorithm>

using std::pair;

#include <string>
using std::string;

#define SYMBOL_NAME string
#define SYMBOL_TYPE int

#define SYMBOL_TYPE_OR_CHAR SYMBOL_TYPE

#define symbolName first
#define symbolType second

const SYMBOL_TYPE NONE = -1; // no tokenValue

// tokens return by the scanner
const SYMBOL_TYPE EOS = '\0';
const SYMBOL_TYPE NUMBER = 256;
const SYMBOL_TYPE ATOM = 257;
const SYMBOL_TYPE ATOMSC = 258;
const SYMBOL_TYPE VAR = 259;

#include <vector>
using std::vector;

vector<pair<SYMBOL_NAME, SYMBOL_TYPE>> symtable;

bool isSpecialCh(char c) {
  return c == '+'
      // || c == '=' // ... the matching operator
         || c == '-'
         || c == '*'
         || c == '/'
         || c == '<'
         || c == '>'
         || c == '.'
         || c == '&'
         || c == '\\'
         || c == '~'
         || c == '^'
         || c == '$'
         || c == '#'
         || c == '@'
         || c == '?'
         || c == ':';
}

bool symbolExist(string s, int & val) {
  bool found = false;
  val = -1;
  vector<pair<SYMBOL_NAME, SYMBOL_TYPE>>::iterator it = find_if(symtable.begin(), symtable.end(), [s](pair<SYMBOL_NAME, SYMBOL_TYPE> ele) {
    return ele.first == s;
  });

  found = symtable.end() != it;
  if (found)
   val = it - symtable.begin();

  return found;
}

#endif
