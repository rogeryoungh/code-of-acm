#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int P = 1E9 + 7;

// @description 矩阵快速幂

struct QMtx {
	int n;
	vector<ll> m;
	QMtx(int a) : n(a), m(n * n) {}
	auto operator[](int i) {
		return m.begin() + i * n;
	}
	auto operator[](int i) const {
		return m.begin() + i * n;
	}
	static QMtx E(int n) {
		QMtx e(n);
		for (int i = 0; i < n; i++) {
			e[i][i] = 1;
		}
		return e;
	}
	QMtx pow(ll w);
};

QMtx operator*(const QMtx &lhs, const QMtx &rhs) {
	assert(lhs.n == rhs.n);
	int n = lhs.n;
	QMtx u(n);
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			ll t = lhs[i][k];
			for (int j = 0; j < rhs.n; j++) {
				(u[i][j] += rhs[k][j] * t) %= P;
			}
		}
	}
	return u;
}

QMtx QMtx::pow(ll w) {
	QMtx ret = QMtx::E(n), a = *this;
	for (; w > 0; w >>= 1) {
		if (w & 1)
			ret = a * ret;
		a = a * a;
	}
	return ret;
}

istream &operator>>(istream &is, QMtx &m) {
	ll t;
	for (int i = 0; i < m.n * m.n; i++) {
		is >> t;
		m.m[i] = (t + P) % P;
	}
	return is;
}

ostream &operator<<(ostream &os, QMtx &m) {
	for (int i = 0; i < m.n * m.n; i++) {
		os << m.m[i] << " \n"[(i + 1) % m.n == 0];
	}
	return os;
}

int main() {
	ll n, k;
	cin >> n >> k;
	QMtx mtx(n);
	cin >> mtx;
	QMtx ans = mtx.pow(k);
	cout << ans;
	return 0;
}
