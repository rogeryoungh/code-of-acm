#include <vector>
using namespace std;

const int P = 998244353;

// @description 取模整数

#define OPERATOR(U, op)                                       \
	friend inline U operator op(const U &lhs, const U &rhs) { \
		return U(lhs) op## = rhs;                             \
	}

struct Z {
	int v;
	Z(int a = 0) : v(a) {}
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
	Z operator-() const {
		return v == 0 ? 0 : P - v;
	}
	Z &operator/=(const Z &m) {
		return *this *= m.inv();
	}
	OPERATOR(Z, /);
	explicit operator int() const {
		return v;
	}
};

// @description 预处理逆元、阶乘、阶乘逆元

vector<Z> iv{1, 1}, fac{1}, ifac{1};

void pre_all(int n) {
	iv.resize(n + 1), fac.resize(n + 1), ifac.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i;
	}
	ifac[n] = fac[n].inv(), iv[n] = Z(n).inv();
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1);
		iv[i] = ifac[i] * fac[i - 1];
	}
}

// @description 组合数

Z C(int n, int m) {
	return fac[n] * ifac[m] * ifac[n - m];
}
