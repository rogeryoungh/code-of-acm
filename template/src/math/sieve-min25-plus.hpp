#include "basic/index.hpp"

#include "basic/modint/modint.hpp"

std::vector<bool> not_p;
std::vector<int> primes;
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
	std::vector<bool> not_p;
	std::vector<int> pri;
	std::vector<Z> sum;
	Z fp(ll pk) {
		return Z(pk) * ((pk - 1) % P);
	}
	int id(ll x) {
		return x <= sn ? x : m - (n / x) + 1;
	}
	Min25(ll u) : n(u), sn(sqrt(n) + 1), not_p(sn + 1), sum(sn * 2 + 5) {
		std::vector<Z> s2(sn * 2 + 5), s1(sn * 2 + 5);
		std::vector<ll> w(sn * 2 + 5);
		for (ll l = 1, r; l <= n; l = r + 1) {
			w[++m] = r = n / (n / l);
			Z mr = r % P;
			s1[m] = mr * (mr + 1) / 2 - 1;
			s2[m] = mr * (mr + 1) * (2 * mr + 1) / 6 - 1;
		}
		pri = primes, pri.insert(pri.begin(), 0);
		int cnt = 0;
		for (int i = 1, pi = pri[i]; pi <= sn; pi = pri[++i], cnt = i) {
			for (int j = m; pi <= w[j] / pi; j--) {
				s1[j] -= pi * (s1[id(w[j] / pi)] - s1[pri[i - 1]]);
				s2[j] -= Z(pi) * pi * (s2[id(w[j] / pi)] - s2[pri[i - 1]]);
			}
		}
		for (int i = 2; i <= m; i++) {
			sum[i] = s1[i] = s2[i] - s1[i];
		}
		for (int i = cnt, pi = pri[i]; i >= 1; pi = pri[--i]) {
			for (int j = m; pi <= w[j] / pi; j--) {
				ll pw = pi;
				for (int k = 1; pw <= w[j] / pi; k++, pw *= pi) {
					sum[j] += fp(pw) * (sum[id(w[j] / pw)] - s1[pi]) + fp(pw * pi);
				}
			}
		}
	}
	Z eval(ll u) {
		return sum[id(u)] + 1;
	}
};
