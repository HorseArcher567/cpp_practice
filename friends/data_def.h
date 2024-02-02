#ifndef CPP_PRACTICE_FRIEND_DATA_DEF_H_
#define CPP_PRACTICE_FRIEND_DATA_DEF_H_

#define Unused(x) (void)(x)

class X {
 private:
	int a = 0;
	enum { e = 100 };

	friend void friend_set(X *);

 public:
	int getA() const { return a; }
	static int getE() { return e; }
};
void friend_set(X *p) { p->a = X::e; }

class F;
class Y {
 private:
	int a = 0;
	friend class F;

 public:
	int getA() const { return a; }
};

class F {
 private:
	int b = 0;

 public:
	static void setA(Y *p, int a) { p->a = a; }
	int getA(Y *p) const {
		Unused(b);
		return p->a;
	}
};

#endif //CPP_PRACTICE_FRIEND_DATA_DEF_H_
