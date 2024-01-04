//
// Created by 杨鹏 on 2024/1/4.
//

#ifndef CPP_PRACTICE_POLYMORPHISM_FUNCTION_OVERLOADING_H_
#define CPP_PRACTICE_POLYMORPHISM_FUNCTION_OVERLOADING_H_

#include <iostream>

namespace function_overloading {

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

	const char* foo(long a, long b) const {
		Unused(a);
		Unused(b);
		Unused(s);
		return "Base::foo(long, long)";
	}

	long s = 10;
};
}

#endif //CPP_PRACTICE_POLYMORPHISM_FUNCTION_OVERLOADING_H_
