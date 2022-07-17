#include <vector>
using namespace std;

// @description 二维数组

template <class T>
struct Mtx {
	int x, y;
	vector<T> m;
	Mtx(int a, int b) : x(a), y(b), m(a * b) {}
	auto operator[](int i) {
		return m.begin() + i * y;
	}
	auto operator[](int i) const {
		return m.begin() + i * y;
	}
};
