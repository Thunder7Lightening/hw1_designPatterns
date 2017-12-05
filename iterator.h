#ifndef ITERATOR_H
#define ITERATOR_H

#include "atom.h"
#include "struct.h"
#include "list.h"

#include <stack>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};

/**
 * Implement the interface through your design,
 * and do not modify the function signature of each.
*/

// TODO
template<typename T>
class BFSIterator :public Iterator<T> {
public:
  BFSIterator(T term): _index(0)
  {
    _traverseSequence.push_back(new Atom("test"));
    _traverseSequence.push_back(new Atom("test"));
  }

  virtual void first()
  {
    _index = 0;
  }

  virtual void next()
  {
    _index++;
  }

  virtual T currentItem() const
  {
    return _traverseSequence.at(_index);
  }

  virtual bool isDone() const
  {
    return _index >= _traverseSequence.size();
  }

public:
  int _index;
  vector<T> _traverseSequence;
};

// TODO
template<typename T>
class DFSIterator :public Iterator<T> {
public:
  DFSIterator(Term *term):testTerm(term){}

  virtual void first(){}
  virtual void next(){}
  virtual T currentItem() const { return testTerm; }
  virtual bool isDone() const {}

private:
  Term *testTerm;
};












template<typename T>
class NullIterator :public Iterator<T>{
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  T currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

template<typename T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;

  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }

private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template<typename T>
class ListIterator :public Iterator<T> {
public:
  ListIterator(List *list): _index(0), _list(list) {}

  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  List* _list;
};

#endif
