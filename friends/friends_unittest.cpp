#include <gtest/gtest.h>
#include "data_def.h"

TEST(FriendTest, FriendFunciont) {
	X x;
	EXPECT_EQ(x.getA(), 0);
	friend_set(&x);
	EXPECT_EQ(x.getA(), x.getE());
}

TEST(FriendTest, FriendClass) {
	Y y;
	EXPECT_EQ(y.getA(), 0);
	int a = 1;
	F::setA(&y, a);
	F f;
	EXPECT_EQ(f.getA(&y), a);
}