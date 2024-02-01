//
// Created by 杨鹏 on 2024/1/4.
//

#ifndef CPP_PRACTICE_POLYMORPHISM_FUNCTION_HIDING_H_
#define CPP_PRACTICE_POLYMORPHISM_FUNCTION_HIDING_H_

namespace function_hiding {
#define Unused(x) ((void)x)

class Base {
	public:
		Base() = default;
		virtual ~Base() = default;

		const char *foo(const long a) const {
			Unused(a);
			Unused(s);
			return "Base::foo(long)";
		}

		const char *bar() const {
			return "Base::bar()";
		}

		long s = 10;
};

class Derived final : public Base {
	public:
		Derived() = default;
		~Derived() override = default;

		const char *foo(const int a, const int b) const {
			Unused(a);
			Unused(b);
			Unused(s);
			return "Derived::foo(long, long)";
		}

		// WARNING: the compiler believes that function overriding should be used here.
		const char *bar() const {
			return "Derived::bar()";
		}
};
}

#endif //CPP_PRACTICE_POLYMORPHISM_FUNCTION_HIDING_H_
