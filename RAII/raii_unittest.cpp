#include <iostream>
#include <gtest/gtest.h>

TEST(RAIITest, SmartPointer) {
	std::weak_ptr<int> w;
	EXPECT_EQ(w.expired(), true);

	{
		auto s = std::make_shared<int>(10);
		w = s;
		EXPECT_EQ(w.expired(), false);
	}

	EXPECT_EQ(w.expired(), true);
}

TEST(RAIITest, MutualExclusion) {
	std::mutex m;
	{
		std::lock_guard<std::mutex> l(m);
		EXPECT_EQ(m.try_lock(), false);
	}
	EXPECT_EQ(m.try_lock(), true);
}