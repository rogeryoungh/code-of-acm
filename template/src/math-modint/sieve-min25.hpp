#include "basic/index.hpp"

#include "math-modint/basic.hpp"

V<bool> not_p;
V<int> primes;
void Euler(int n) {
	not_p.resize(n);
	for (int i = 2; i < n; i++) {
		if (not not_p[i])
			primes.push_back(i);
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0)
				break;
		}
	}
}

struct Min25 {
	ll n, sn, m = 0;
	V<bool> not_p;
	V<int> pri;
	V<Z> sum;
	Z fp(int p, int k) {
		Z pk = Z(p).pow(k);
		return pk * (pk - 1);
	}
	int id(ll x) {
		return x <= sn ? x : m - (n / x) + 1;
	}
	Min25(ll u) : n(u), sn(sqrt(n) + 1), not_p(sn + 1), sum(sn * 2 + 5) {
		V<Z> s2(sn * 2 + 5), s1(sn * 2 + 5);
		V<ll> w(sn * 2 + 5);
		for (ll l = 1, r; l <= n; l = r + 1) {
			w[++m] = r = n / (n / l);
			Z mr = r % P;
			s1[m] = mr * (mr + 1) / 2 - 1;
			s2[m] = mr * (mr + 1) * (2 * mr + 1) / 6 - 1;
		}
		pri = primes, pri.insert(pri.begin(), 0);
		for (int i = 1, pi = pri[i]; pi <= sn; pi = pri[++i]) {
			for (int j = m; pi <= w[j] / pi; j--) {
				s1[j] -= pi * (s1[id(w[j] / pi)] - s1[pri[i - 1]]);
				s2[j] -= Z(pi) * pi * (s2[id(w[j] / pi)] - s2[pri[i - 1]]);
			}
		}
		for (int i = 2; i <= m; i++) {
			sum[i] = s2[i] - s1[i];
		}
	}
	Z eval() {
		return F(n, 0) + 1;
	}
	Z F(ll u, int k) {
		if (u <= pri[k])
			return 0;
		Z ret = sum[id(u)] - sum[pri[k]];
		for (int i = k + 1; i < pri.size() && 1ll * pri[i] * pri[i] <= u; i++) {
			ll pi = pri[i], pc = pi;
			for (int c = 1; pc * pi <= u; c++, pc *= pi)
				ret += fp(pi, c) * F(u / pc, i) + fp(pi, c + 1);
		}
		return ret;
	}
};
