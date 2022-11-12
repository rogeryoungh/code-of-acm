#include "basic/index.hpp"

// @description 二维数组

template <class T>
struct VV {
	int x, y;
	V<T> m;
	VV(int a, int b, const T &v = T()) : x(a), y(b), m(a * b, v) {}
	auto operator[](int i) {
		return m.begin() + i * y;
	}
	auto operator[](int i) const {
		return m.begin() + i * y;
	}
};
