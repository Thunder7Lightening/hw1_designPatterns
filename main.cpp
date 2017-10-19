#include <gtest/gtest.h>
#include "utAtom.h"
#include "utNumber.h"
#include "utVariable.h"
#include "utStruct.h"

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	system("pause");
	return ret;
}