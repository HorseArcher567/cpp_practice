#ifndef CPP_PRACTICE_CAST_DATA_DEF_H_
#define CPP_PRACTICE_CAST_DATA_DEF_H_

#include <iostream>

class Bird {
 public:
	Bird() = default;
	int count = 1;
};

class Fish {
 public:
	Fish() = default;
	explicit operator Bird() {
		return {10};
	}
};

template<typename T>
class Cat {
 public:
	explicit Cat(T &t) : food(t) {
	}
	const char *FavoriteFood() {
		return typeid(food).name();
	}

 private:
	T food;
};

class Grandpa {
 public:
	Grandpa() = default;
	virtual ~Grandpa() = default;

	long a = 0xaa;
};

class Parent : public Grandpa {
 public:
	Parent() = default;
	~Parent() override = default;

	long b = 0xbb;
};

class Mother {
 public:
	Mother() = default;
	virtual ~Mother() = default;

	long d = 0xdd;
};

class Son final : public Parent, public Mother {
 public:
	Son() = default;
	~Son() override = default;

	long c = 0xcc;
};

#endif //CPP_PRACTICE_CAST_DATA_DEF_H_
