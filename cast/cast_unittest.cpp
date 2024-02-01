#include <gtest/gtest.h>
#include "data_def.h"

TEST(CastTest, StaticCast) {
	constexpr auto i = static_cast<int>('a');
	EXPECT_EQ(97, i);

	constexpr auto d = static_cast<double>(i);
	EXPECT_EQ(97.0, d);

	Fish fish;
	auto bird = static_cast<Bird>(fish);
	EXPECT_EQ(bird.count, 10);
	auto cat = static_cast<Cat<Fish>>(fish);
	EXPECT_STREQ(typeid(fish).name(), cat.FavoriteFood());
}

TEST(CastTest, DynamicCast) {
	auto son = Son();
	Parent *parent = &son;
	Grandpa *grandpa = &son;
	Mother *mother = &son;
	EXPECT_EQ(&son, parent);
	EXPECT_EQ(&son, grandpa);
	EXPECT_NE(reinterpret_cast<uintptr_t *>(&son), reinterpret_cast<uintptr_t *>(mother));

	EXPECT_EQ(dynamic_cast<Son *>(mother), &son);
	EXPECT_EQ(dynamic_cast<Son *>(grandpa), &son);
	EXPECT_EQ(dynamic_cast<Son *>(parent), &son);

	EXPECT_EQ(dynamic_cast<Parent *>(grandpa), parent);
}

TEST(CastTest, ReinterpretCast) {
	unsigned int l = 0x11223344;
	auto *p = reinterpret_cast<u_char *> (&l);

	union EndianCheck {
		u_short value;
		u_char bytes[2];
	} u = {0xaabb};
	if (u.bytes[0] == 0xaa) {
		EXPECT_EQ(0x33, *p);
		EXPECT_EQ(0x44, *(p + 1));
	} else {
		EXPECT_EQ(0x44, *p);
		EXPECT_EQ(0x33, *(p + 1));
	}
}

TEST(CastTest, ConstCast) {
	const int c = 123;
	int &r = const_cast<int &>(c);
	r = 456;
	EXPECT_EQ(456, *&c);
	std::cout << c << ", " << *&c << ", " << r << std::endl;
}
