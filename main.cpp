#include <iostream>
using namespace std;

int main() {
	const int c = 10;
	int &r = const_cast<int &>(c);
	r = 20;
	cout << c << ", " << *&c << ", " << r << endl;

	constexpr int x = 10;
	int &y = const_cast<int &>(x);
	y = 20;
	cout << x << ", " << *&x << ", " << y << endl;

	return 0;
}
