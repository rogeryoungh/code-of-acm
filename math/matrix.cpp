#include <vector>
#include <iostream>
#include <cassert>
using ll = long long;
using namespace std;

const int P = 1E9 + 7;

// @description 矩阵乘法
// @problem https://loj.ac/p/100

struct Mtx {
	int x, y;
	vector<ll> m;
	Mtx(int a, int b) : x(a), y(b), m(x * y) {}
	auto operator[](int i) {
		return m.begin() + i * y;
	}
	auto operator[](int i) const {
		return m.begin() + i * y;
	}
};

Mtx operator*(const Mtx &lhs, const Mtx &rhs) {
	assert(lhs.y == rhs.x);
	Mtx u(lhs.x, rhs.y);
	for (int i = 0; i < lhs.x; i++) {
		for (int k = 0; k < rhs.x; k++) {
			ll t = lhs[i][k];
			for (int j = 0; j < rhs.y; j++) {
				(u[i][j] += rhs[k][j] * t) %= P;
			}
		}
	}
	return u;
}

istream &operator>>(istream &is, Mtx &m) {
	ll t;
	for (int i = 0; i < m.x * m.y; i++) {
		is >> t;
		m.m[i] = (t + P) % P;
	}
	return is;
}

ostream &operator<<(ostream &os, Mtx &m) {
	for (int i = 0; i < m.x * m.y; i++) {
		os << m.m[i] << " \n"[(i + 1) % m.y == 0];
	}
	return os;
}
