#pragma once
#include "../base.hpp"
#include "./miller-rabin.hpp"

// #region snippet
i64 pollard_rho(i64 N) {
	if (N % 2 == 0)
		return 2;
	if (miller_rabin(N))
		return N;
	while (true) {
		auto f = [N, c = rand() % (N - 1) + 1](i64 x) {
			return (i128(x) * x + c) % N;
		};
		i64 x = 0, y = 0, p = 1, q = 1;
		do {
			int w = 128;
			do {
				p = q, x = f(x), y = f(f(y));
				q = i128(p) * std::abs(x - y) % N;
			} while (w-- && q != 0);
			i64 d = std::gcd(p, N);
			if (d > 1 && d != N)
				return d;
		} while (x != y);
	}
}

auto factor(i64 x) {
	std::vector<i64> v;
	if (x == 1)
		return v;
	auto dfs = [&](auto &&self, i64 u) -> void {
		i64 fac = pollard_rho(u);
		if (fac == u)
			v.push_back(u);
		else
			self(self, fac), self(self, u / fac);
	};
	dfs(dfs, x);
	std::sort(v.begin(), v.end());
	return v;
}
// #endregion snippet
