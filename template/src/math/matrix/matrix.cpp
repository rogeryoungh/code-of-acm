#include "basic/index.hpp"

#include "basic/vec2.cpp"

// @description 矩阵乘法

template <class T>
VV<T> operator*(const VV<T> &lhs, const VV<T> &rhs) {
	assert(lhs.y == rhs.x);
	VV<T> u(lhs.x, rhs.y);
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
std::istream &operator>>(std::istream &is, VV<T> &m) {
	for (int i = 0; i < m.x * m.y; i++)
		is >> m.m[i];
	return is;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const VV<T> &m) {
	for (int i = 0; i < m.x * m.y; i++)
		os << m.m[i] << " \n"[(i + 1) % m.y == 0];
	return os;
}
