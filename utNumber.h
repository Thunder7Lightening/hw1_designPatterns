#ifndef UTNUMBER_H
#define UTNUMBER_H

#include <gtest/gtest.h>
#include "number.h"

TEST(Number, integer_constructor)
{
	Number number1(1);
	ASSERT_EQ("1", number1.symbol());
	ASSERT_EQ("1", number1.value());
}

TEST(Number, double_constructor)
{
	Number number3_14(3.14);
	ASSERT_EQ("3.14", number3_14.symbol());
	ASSERT_EQ("3.14", number3_14.value());
}

// ?- 3.14=3.14.
// true
TEST(Number, match_success)
{
	Number number3_14(3.14);
	ASSERT_TRUE(number3_14.match(&number3_14));
}

// ?- 1=3.14.
// false
TEST(Number, match_failure)
{
	Number number1(1);
	Number number3_14(3.14);
	ASSERT_FALSE(number1.match(&number3_14));
}

#endif // !UTNUMBER_H