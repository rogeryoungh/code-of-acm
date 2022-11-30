#include "basic/index.hpp"

#include "basic/qpow/qpow-P.hpp"

// @description 取模整数

#include "using/operator-marco.hpp"

struct Z {
	int v;
	Z(ll a = 0) : v((a % P + P) % P) {}
	Z &operator=(const int &m) {
		v = m;
		return *this;
	}
	Z &operator+=(const Z &m) {
		v = (v += m.v) >= P ? v - P : v;
		return *this;
	}
	Z &operator-=(const Z &m) {
		v = (v -= m.v) < 0 ? v + P : v;
		return *this;
	}
	Z &operator*=(const Z &m) {
		v = 1ll * v * m.v % P;
		return *this;
	}
	OPERATOR(Z, Z, +);
	OPERATOR(Z, Z, -);
	OPERATOR(Z, Z, *);
	Z pow(int n) const {
		return qpow(v, n);
	}
	Z inv() const {
		return pow(P - 2);
	}
	// useless
	Z operator-() const {
		return v == 0 ? 0 : P - v;
	}
	Z &operator/=(const Z &m) {
		return *this *= m.inv();
	}
	OPERATOR(Z, Z, /);
	auto approx(int A = 1E3) {
		int x = v, y = P, a = 1, b = 0;
		while (x > A) {
			std::swap(x, y), std::swap(a, b);
			a -= x / y * b, x %= y;
		}
		return std::make_pair(x, a);
	}
};

std::istream &operator>>(std::istream &is, Z &z) {
	return is >> z.v;
}

std::ostream &operator<<(std::ostream &os, const Z &z) {
	return os << z.v;
}
