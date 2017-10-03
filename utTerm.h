#ifndef UTTERM_H
#define UTTERM_H

#include <gtest/gtest.h>
#include "number.h"
#include "atom.h"
#include "variable.h"

//test Number.value()
TEST (Number,ctor)
{
	Number number25("25");
	ASSERT_EQ("25", number25.value());
}

//test Number.symbol()
TEST (Number, symbol)
{
	Number number25("25");
	ASSERT_EQ("25", number25.symbol());
}

//?- 25=25.
//true.
TEST (Number, matchSuccess)
{
	Number number25("25");
	ASSERT_TRUE(number25.match(number25));
}

//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue)
{
	Number number25("25");
	Number number0("0");
	ASSERT_FALSE(number25.match(number0));
}

//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant)
{
	Number number25("25");
	Atom tom("tom");
	ASSERT_FALSE(number25.match(tom));
}

//?- 25=X.
//true.
TEST (Number, matchSuccessToVar)
{
	Number number25("25");
	Variable X("X");
	ASSERT_TRUE(number25.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant)
{
	Atom tom("tom");
	Number number25("25");
	ASSERT_FALSE(tom.match(number25));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar)
{
	Atom tom("tom");
	Variable X("X");
	ASSERT_TRUE(tom.match(X));
	ASSERT_EQ("tom", X.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant)
{
	Variable X("X");
	Atom tom("tom");
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(tom.match(X));
	ASSERT_EQ(tom.value(), X.value());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant)
{
	Variable X("X");
	Atom jerry("jerry");
	Atom tom("tom");
	ASSERT_TRUE(X.match(jerry));
	ASSERT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber)
{
	Variable X("X");
	Number number5("5");
	ASSERT_TRUE(X.match(number5));
	ASSERT_EQ("5", X.value());
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers)
{
	Variable X("X");
	Number number25("25");
	Number number100("100");
	ASSERT_TRUE(X.match(number25));
	ASSERT_FALSE(X.match(number100));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber)
{
	Variable X("X");
	Atom tom("tom");
	Number number25("25");
	ASSERT_TRUE(X.match(tom));
	ASSERT_FALSE(X.match(number25));
}

//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2)
{
	Atom tom("tom");
	Number number25("25");
	Variable X("X");
	ASSERT_TRUE(tom.match(X));
	ASSERT_FALSE(number25.match(X));
}

//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom)
{
	Variable X("X");
	Atom tom("tom");
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(X.match(tom));
}

#endif
