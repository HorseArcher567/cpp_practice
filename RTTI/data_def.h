#ifndef CPP_PRACTICE_RTTI_DATA_DEF_H_
#define CPP_PRACTICE_RTTI_DATA_DEF_H_
#include <iostream>
using namespace std;

class Base {
 public:
	Base() = default;
	virtual ~Base() = default;
	virtual void show() {
		std::cout << "Base" << std::endl;
	}
};

class Derived : public Base {
 public:
	Derived() = default;
	~Derived() override = default;
	void show() override {
		std::cout << "Derived" << std::endl;
	}
};

#endif //CPP_PRACTICE_RTTI_DATA_DEF_H_
