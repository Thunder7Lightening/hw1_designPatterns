#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "atom.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "iterator.h"

// iterate s(1, t(X,2), Y)
TEST(iterator, first) {
  // create s(1, t(X,2), Y)
  Variable X("X");
  Number two(2);
  Number one(1);
  Struct t(Atom("t"), { &X, &two });
  Variable Y("Y");
  Struct s(Atom("s"), { &one, &t, &Y });

  // iterate
  Iterator *itStruct = s.createIterator();
  itStruct->first();
  ASSERT_EQ("1", itStruct->currentItem()->symbol());
  ASSERT_FALSE(itStruct->isDone());
  itStruct->next();
  ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
  ASSERT_FALSE(itStruct->isDone());
  itStruct->next();
  ASSERT_EQ("Y", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_TRUE(itStruct->isDone());
}

// iterate t(X,2) in s(1, t(X,2), Y)
TEST(iterator, nested_iterator) {
  // create s(1, t(X,2), Y)
  Variable X("X");
  Number two(2);
  Number one(1);
  Struct t(Atom("t"), { &X, &two });
  Variable Y("Y");
  Struct s(Atom("s"), { &one, &t, &Y });

  // find t(X,2)
  Iterator *it = s.createIterator();
  it->first();
  it->next();

  // iterate
  it = it->currentItem()->createIterator();
  it->first();
  ASSERT_EQ("X", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_TRUE(it->isDone());
}

// iterate [1, t(X,2), Y]
TEST(iterator, firstList) {
    // create [1, t(X,2), Y]
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });

    // iterate
    Iterator *it = l.createIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
  }

// iterate 1
TEST(iterator, NullIterator){
  Number one(1);

  NullIterator nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());

  Iterator *it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

// Here are the 8 new Tests below
// combo1(bigMac(bun, beefPatty), coke)
// TEST(ITERATOR, BFSIteratorWithSimpleTestData)
// {
//   // create combo1(bigMac(bun, beefPatty), coke)
//   Atom coke("coke");
//   Atom bun("bun");
//   Atom beefPatty("beefPatty");
//   Struct bigMac(Atom("bigMac"), { &bun, &beefPatty });
//   Struct combo1(Atom("combo1"), { &bigMac, &coke });
//
//   // iterate it by BSF
//   Iterator *it = combo1.createBFSIterator();
//   it->first();
//   ASSERT_TRUE("bigmac", it->currentItem());
// }

#endif
