#pragma once
#include "../base.hpp"
#include "../base/vec2d.hpp"

// #region snippet
template <class T>
vec2d<T> operator*(const vec2d<T> &lhs, const vec2d<T> &rhs) {
	assert(lhs.y == rhs.x);
	vec2d<T> u(lhs.x, rhs.y);
	for (int i = 0; i < lhs.x; i++) {
		for (int k = 0; k < rhs.x; k++) {
			T t = lhs[i][k];
			for (int j = 0; j < rhs.y; j++)
				u[i][j] += rhs[k][j] * t;
		}
	}
	return u;
}

template <class T>
std::istream &operator>>(std::istream &is, vec2d<T> &m) {
	for (int i = 0; i < m.x * m.y; i++)
		is >> m.m[i];
	return is;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const vec2d<T> &m) {
	for (int i = 0; i < m.x * m.y; i++)
		os << m.m[i] << " \n"[(i + 1) % m.y == 0];
	return os;
}
// #endregion snippet
