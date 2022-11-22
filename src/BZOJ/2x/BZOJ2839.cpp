#include <bits/stdc++.h>

template <class T>
using V = std::vector<T>;
using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

const int P = 1E9 + 7;

// @description 快速幂(i32, P)

int qpow(int a, int b = P - 2, int m = P) {
	int ret = 1 % m;
	for (; b > 0; b /= 2) {
		if (b % 2 == 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

// @description 取模整数

// clang-format off
#define OPERATOR(U, V, op)	\
friend inline U operator op(const U &l, const V &r) {	\
	return U(l) op##= r;	\
}
// clang-format on

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

// @description 预处理逆元、阶乘、阶乘逆元

V<Z> iv, fac, ifac;

void pre_all(int u) {
	int l = iv.size(), n = l * 2;
	if (u <= l)
		return;
	iv = fac = ifac = V<Z>(n + 1, 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i;
	}
	ifac[n] = fac[n].inv(), iv[n] = Z(n).inv();
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1);
		iv[i] = ifac[i] * fac[i - 1];
	}
	pre_all(u);
}

// @description 组合数

Z C(int n, int m) {
	return fac[n] * ifac[m] * ifac[n - m];
}

int main() {
	int n, k;
	std::cin >> n >> k;
	pre_all(n + 1);
	V<Z> p2(n + 1);
	for (int i = 0; i <= n; i++) {
		p2[i] = i == 0 ? 2 : p2[i - 1] * p2[i - 1];
	}
	Z ans = 0, zi = 1;
	for (int i = k; i <= n; i++) {
		ans += zi * ifac[i - k] * ifac[n - i] * (p2[n - i] - 1);
		zi *= -1;
	}
	std::cout << ans * fac[n] * ifac[k];
	return 0;
}
