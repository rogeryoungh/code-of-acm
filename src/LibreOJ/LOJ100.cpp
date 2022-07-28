#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int P = 1E9 + 7;

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

int main() {
	int n, p, m;
	cin >> n >> p >> m;
	Mtx A(n, p), B(p, m);
	cin >> A >> B;
	Mtx ans = A * B;
	cout << ans;
	return 0;
}
