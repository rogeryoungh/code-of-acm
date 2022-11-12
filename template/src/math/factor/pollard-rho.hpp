#include "basic/index.hpp"

#include "math/miller-rabbin.hpp"

// @description Pollard Rho

ll pollard_rho(ll N) {
	if (N % 2 == 0)
		return 2;
	if (miller_rabbin(N))
		return N;
	while (true) {
		auto f = [N, c = rand() % (N - 1) + 1](ll x) {
			return (i128(x) * x + c) % N;
		};
		ll x = 0, y = 0, p = 1, q = 1;
		do {
			int w = 128;
			do {
				p = q, x = f(x), y = f(f(y));
				q = i128(p) * std::abs(x - y) % N;
			} while (w-- && q != 0);
			ll d = std::__gcd(p, N);
			if (d > 1 && d != N)
				return d;
		} while (x != y);
	}
}

auto factor(ll x) {
	V<ll> v;
	if (x == 1)
		return v;
	std::function<void(ll)> dfs = [&](ll u) {
		ll fac = pollard_rho(u);
		if (fac == u)
			v.push_back(u);
		else
			dfs(fac), dfs(u / fac);
	};
	dfs(x);
	sort(v.begin(), v.end());
	return v;
}
