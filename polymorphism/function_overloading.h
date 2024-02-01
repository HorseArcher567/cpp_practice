#ifndef CPP_PRACTICE_POLYMORPHISM_FUNCTION_OVERLOADING_H_
#define CPP_PRACTICE_POLYMORPHISM_FUNCTION_OVERLOADING_H_

namespace function_overloading {
#define Unused(x) ((void)x)

class Base final {
	public:
		Base() = default;
		~Base() = default;

		const char *foo(const long a) const {
			Unused(a);
			Unused(s);
			return "Base::foo(long)";
		}

		const char *foo(const long a, const long b) const {
			Unused(a);
			Unused(b);
			Unused(s);
			return "Base::foo(long, long)";
		}

		long s = 10;
};
}

#endif //CPP_PRACTICE_POLYMORPHISM_FUNCTION_OVERLOADING_H_
