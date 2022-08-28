#include "basic/index.hpp"

using i128 = __int128;

const ll P = 998244353998244353;

// @description 取模整数

#define OPERATOR(U, op)                                       \
	friend inline U operator op(const U &lhs, const U &rhs) { \
		return U(lhs) op## = rhs;                             \
	}

struct Z {
	ll v;
	Z(ll a = 0) : v(a % P) {}
	Z(i128 a) : v(a % P) {}
	Z &operator+=(const Z &m) {
		v = (v += m.v) >= P ? v - P : v;
		return *this;
	}
	Z &operator-=(const Z &m) {
		v = (v -= m.v) < 0 ? v + P : v;
		return *this;
	}
	Z &operator*=(const Z &m) {
		v = i128(v) * m.v % P;
		return *this;
	}
	OPERATOR(Z, +);
	OPERATOR(Z, -);
	OPERATOR(Z, *);
	Z pow(ll n) const {
		ll ret = P != 1, a = v;
		for (; n; n /= 2) {
			if (n % 2 == 1)
				ret = i128(ret) * a % P;
			a = i128(a) * a % P;
		}
		return ret;
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
	OPERATOR(Z, /);
};

istream &operator>>(istream &is, Z &z) {
	return is >> z.v;
}

ostream &operator<<(ostream &os, const Z &z) {
	return os << z.v;
}
