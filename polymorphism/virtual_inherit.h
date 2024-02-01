//
// Created by yp on 2023/12/27.
//

#ifndef CPP_PRACTICE_POLYMORPHISM_VIRTUAL_INHERIT_H_
#define CPP_PRACTICE_POLYMORPHISM_VIRTUAL_INHERIT_H_

namespace virtual_inherit {
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

class BaseA : virtual public Base {
 public:
	BaseA() = default;
	~BaseA() override = default;

	long foo() override {
		printf("BaseA::foo %ld\n", a);
		return a;
	}

	long a = 20;
};

class BaseB : virtual public Base {
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

	virtual long bar() {
		printf("BaseC::bar %ld\n", c);
		return c;
	}

	long c = 40;
};

class Derived final : public BaseA, public BaseB, public BaseC {
 public:
	Derived() = default;
	~Derived() override = default;

	long foo() override {
		printf("Derived::foo %ld\n", d);
		return d;
	}

	long bar() override {
		printf("Derived::bar %ld\n", d);
		return d;
	}

	long d = 50;
};
}

#endif //CPP_PRACTICE_POLYMORPHISM_VIRTUAL_INHERIT_H_
