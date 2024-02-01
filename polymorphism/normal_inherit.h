//
// Created by 杨鹏 on 2023/12/27.
//

#ifndef CPP_PRACTICE_NORMAL_INHERIT_H
#define CPP_PRACTICE_NORMAL_INHERIT_H

namespace normal_inherit {
class Base {
	public:
		Base() = default;
		virtual ~Base() = default;

		virtual long foo() {
			printf("Base::foo %ld\n", s);
			return s;
		}

		long s = 10;
};

class BaseA : public Base {
	public:
		BaseA() = default;
		~BaseA() override = default;

		long foo() override {
			printf("BaseA::foo %ld\n", a);
			return a;
		}

		long a = 20;
};

class BaseB : public Base {
	public:
		BaseB() = default;
		~BaseB() override = default;

		long foo() override {
			printf("BaseB::foo %ld\n", b);
			return b;
		}

		long b = 30;
};

class BaseC {
	public:
		BaseC() = default;
		virtual ~BaseC() = default;

		virtual long foo() {
			printf("BaseC::foo %ld\n", c);
			return c;
		}

		long c = 40;
};

class Derived final : public BaseA, public BaseB, public BaseC {
	public:
		Derived() = default;
		~Derived() override = default;

		long foo() override {
			printf("Derived::foo %ld, %p, %s\n", d, this, typeid(this).name());
			return d;
		}

		long d = 50;
};
}
#endif //CPP_PRACTICE_NORMAL_INHERIT_H
