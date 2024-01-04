//
// Created by 杨鹏 on 2024/1/4.
//

#ifndef CPP_PRACTICE_POLYMORPHISM_FUNCTION_HIDING_H_
#define CPP_PRACTICE_POLYMORPHISM_FUNCTION_HIDING_H_

#include <iostream>

namespace function_hiding {

#define Unused(x) ((void)x)

class Base {
 public:
	Base() = default;
	virtual ~Base() = default;

	const char* foo(long a) const {
		Unused(a);
		Unused(s);
		return "Base::foo(long)";
	}

	const char* bar() const {
		Unused(s);
		return "Base::bar";
	}

	long s = 10;
};

class Derived : public Base {
 public:
	Derived() = default;
	~Derived() override = default;

	const char* foo(int a, int b) const {
		Unused(a);
		Unused(b);
		Unused(s);
		return "Derived::foo(long, long)";
	}

	const char* bar() const {
		Unused(s);
		return "Derived::bar()";
	}
};
}

#endif //CPP_PRACTICE_POLYMORPHISM_FUNCTION_HIDING_H_
