#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int P = 1E9 + 7;

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
};

struct Min25 {
	ll n, sn, m = 0;
	vector<int> primes;
	vector<Z> sum_phi;
	Z fp(int p, int k) {
		return p ^ k;
	}
	int id(ll x) {
		return x <= sn ? x : m - (n / x) + 1;
	}
	Min25(ll u) : n(u), sn(sqrt(n) + 1), sum_phi(sn * 2 + 5) {
		vector<bool> not_p(sn + 1);
		vector<ll> w(sn * 2 + 5);
		for (ll l = 1, r; l <= n; l = r + 1) {
			w[++m] = r = n / (n / l);
		}
		vector<Z> s0(m + 1), s1(m + 1);
		for (int i = 1; i <= m; i++) {
			Z r = w[i] % P;
			s0[i] = r - 1;
			s1[i] = r * (r + 1) / 2 - 1;
		}
		primes.push_back(0);
		for (int i = 2; i <= sn; i++) {
			if (not not_p[i]) {
				primes.push_back(i);
				for (int j = i; j <= (sn - 1) / i; j++)
					not_p[i * j] = true;
				for (int j = m; w[j] >= 1ll * i * i; j--) {
					s1[j] -= i * (s1[id(w[j] / i)] - s1[i - 1]);
					s0[j] -= s0[id(w[j] / i)] - s0[i - 1];
				}
			}
		}
		for (int i = 2; i <= m; i++) {
			sum_phi[i] = s1[i] - s0[i] + 2;
		}
	}
	Z eval() {
		return F(n, 0) + 1;
	}
	Z F(ll u, int k) {
		if (u <= primes[k])
			return 0;
		Z ret = sum_phi[id(u)] - sum_phi[primes[k]];
		for (int i = k + 1; i < primes.size() && 1ll * primes[i] * primes[i] <= u; i++) {
			ll pi = primes[i], pc = pi;
			for (int c = 1; pc * pi <= u; c++, pc *= pi)
				ret += fp(pi, c) * F(u / pc, i) + fp(pi, c + 1);
		}
		return ret;
	}
};

int main() {
	ll n;
	cin >> n;

	cout << Min25(n).eval().v;

	return 0;
}
