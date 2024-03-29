#include "basic/index.hpp"

// @description 取模整数

#include "using/operator-marco.hpp"

template <int P>
struct Z {
	int v;
	Z(ll a = 0) : v(a % P) {}
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
	OPERATOR(Z, +);
	OPERATOR(Z, -);
	OPERATOR(Z, *);
	Z pow(int n) const {
		int ret = P != 1, a = v;
		for (; n; n /= 2) {
			if (n % 2 == 1)
				ret = 1ll * ret * a % P;
			a = 1ll * a * a % P;
		}
		return ret;
	}
	Z inv() const {
		return pow(P - 2);
	}
	// useless
	static int mod() {
		return P;
	}
	Z operator-() const {
		return v == 0 ? 0 : P - v;
	}
	Z &operator/=(const Z &m) {
		return *this *= m.inv();
	}
	OPERATOR(Z, /);
	auto approx(int A = 1E3) const {
		int x = v, y = P, a = 1, b = 0;
		while (x > A) {
			std::swap(x, y), std::swap(a, b);
			a -= x / y * b, x %= y;
		}
		return std::make_pair(x, a);
	}
};
