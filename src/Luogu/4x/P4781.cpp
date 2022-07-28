#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

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

int main() {
	ll n, k;
	cin >> n >> k;
	vector<Z> x(n), y(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i].v >> y[i].v;
	}
	cout << lagrange(x, y, k).v;
	return 0;
}
