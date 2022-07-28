#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int P = 1 << 31;

// @description 取模整数

using Z = ll;

Z qpow(Z a, int b) {
	Z ret = 1;
	for (; b > 0; b /= 2) {
		if (b % 2 == 1)
			ret *= a;
		a *= a;
	}
	return ret;
}

struct Min25_phi {
	ll n, sn, m = 0;
	vector<int> primes;
	vector<Z> sum;
	Z fp(int p, int k) {
		return qpow(p, k - 1) * (p - 1);
	}
	int id(ll x) {
		return x <= sn ? x : m - (n / x) + 1;
	}
	Min25_phi(ll u) : n(u), sn(sqrt(n) + 1), sum(sn * 2 + 5) {
		vector<bool> not_p(sn + 1);
		vector<ll> w(sn * 2 + 5);
		for (ll l = 1, r; l <= n; l = r + 1) {
			w[++m] = r = n / (n / l);
		}
		vector<Z> s0(m + 1), s1(m + 1);
		for (int i = 1; i <= m; i++) {
			Z r = w[i];
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
			sum[i] = s1[i] - s0[i];
		}
	}
	Z eval() {
		return F(n, 0) + 1;
	}
	Z F(ll u, int k) {
		if (u <= primes[k])
			return 0;
		Z ret = sum[id(u)] - sum[primes[k]];
		for (int i = k + 1; i < primes.size() && 1ll * primes[i] * primes[i] <= u; i++) {
			ll pi = primes[i], pc = pi;
			for (int c = 1; pc * pi <= u; c++, pc *= pi) {
				ret += fp(pi, c) * F(u / pc, i) + fp(pi, c + 1);
			}
		}
		return ret;
	}
};

struct Min25_mu {
	ll n, sn, m = 0;
	vector<int> primes;
	vector<Z> sum;
	Z fp(int p, int k) {
		return -(k == 1);
	}
	int id(ll x) {
		return x <= sn ? x : m - (n / x) + 1;
	}
	Min25_mu(ll u) : n(u), sn(sqrt(n) + 1), sum(sn * 2 + 5) {
		vector<bool> not_p(sn + 1);
		vector<ll> w(sn * 2 + 5);
		for (ll l = 1, r; l <= n; l = r + 1) {
			w[++m] = r = n / (n / l);
		}
		vector<Z> s0(m + 1);
		for (int i = 1; i <= m; i++) {
			Z r = w[i];
			s0[i] = r - 1;
		}
		primes.push_back(0);
		for (int i = 2; i <= sn; i++) {
			if (not not_p[i]) {
				primes.push_back(i);
				for (int j = i; j <= (sn - 1) / i; j++)
					not_p[i * j] = true;
				for (int j = m; w[j] >= 1ll * i * i; j--) {
					s0[j] -= s0[id(w[j] / i)] - s0[i - 1];
				}
			}
		}
		for (int i = 2; i <= m; i++) {
			sum[i] = -s0[i];
		}
	}
	Z eval() {
		return F(n, 0) + 1;
	}
	Z F(ll u, int k) {
		if (u <= primes[k])
			return 0;
		Z ret = sum[id(u)] - sum[primes[k]];
		for (int i = k + 1; i < primes.size() && 1ll * primes[i] * primes[i] <= u; i++) {
			ll pi = primes[i], pc = pi;
			for (int c = 1; pc * pi <= u; c++, pc *= pi)
				ret += fp(pi, c) * F(u / pc, i) + fp(pi, c + 1);
		}
		return ret;
	}
};

int main() {
	int T;
	cin >> T;
	while (T--) {
		ll n;
		cin >> n;
		Z ans1 = Min25_phi(n).eval(), ans2 = Min25_mu(n).eval();
		cout << ans1 << ' ' << ans2 << endl;
	}

	return 0;
}
