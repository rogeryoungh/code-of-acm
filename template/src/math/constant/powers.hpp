#include "basic/index.hpp"

#include "basic/qpow/qpow.hpp"

auto powers(int n, int k, int mod) {
	std::vector<bool> isp(n + 1, true);
	std::vector<int> pw(n + 1, 1);
	for (int p = 2; p <= n; ++p)
		if (isp[p]) {
			for (ll j = ll(p) * p; j <= n; j += p)
				isp[j] = false;
			int q = qpow(p, k, mod);
			for (int i = 1; i <= n / p; ++i)
				pw[i * p] = ll(q) * pw[i] % mod;
		}
	pw[0] = qpow(0, k, mod);
	return pw;
}
