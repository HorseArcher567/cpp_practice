#include <gtest/gtest.h>
#include "data_def.h"

TEST(RTTITest, DynamicCast) {
	Base *b = new Derived();
	auto *d = dynamic_cast<Derived *>(b);
	auto r = dynamic_cast<Derived &>(*b);

	EXPECT_NE(d, nullptr);

	delete b;
}

TEST(RTTITest, TypeInfo) {
	Base *b = new Derived();
	auto *d = dynamic_cast<Derived *>(b);
	auto r = dynamic_cast<Derived &>(*b);

	EXPECT_EQ(typeid(Base *), typeid(b));
	EXPECT_EQ(typeid(Derived), typeid(*b));
	EXPECT_EQ(typeid(Derived), typeid(r));
	EXPECT_EQ(typeid(Derived*), typeid(d));
	EXPECT_EQ(typeid(Derived), typeid(*d));

	delete b;
}