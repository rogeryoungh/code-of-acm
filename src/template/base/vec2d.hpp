#pragma once
#include "../base.hpp"

// #region snippet
template <class T>
struct vec2d {
	int x, y;
	std::vector<T> m;
	vec2d(int x, int y, const T &v = T()) : x(x), y(y), m(x * y, v) {}
	auto operator[](int i) {
		return m.begin() + i * y;
	}
	auto operator[](int i) const {
		return m.begin() + i * y;
	}
};
// #endregion snippet
