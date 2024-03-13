#pragma once
#include "../base.hpp"
#include "../base/vec2d.hpp"

// #region snippet
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
