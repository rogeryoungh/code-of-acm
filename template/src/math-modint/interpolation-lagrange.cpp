#include <vector>
using ll = long long;
using namespace std;

const int P = 998244353;

// @problem https://www.luogu.com.cn/problem/P4781

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

// @description 拉格朗日插值

Z lagrange(const vector<Z> &x, const vector<Z> &y, Z k) {
	int n = x.size();
	Z sum = 0;
	for (int i = 0; i < n; i++) {
		Z s1 = 1, s2 = 1;
		for (int j = 0; j < n; j++) {
			if (j == i)
				continue;
			s1 *= k - x[j], s2 *= x[i] - x[j];
		}
		sum += s1 / s2 * y[i];
	}
	return sum;
}