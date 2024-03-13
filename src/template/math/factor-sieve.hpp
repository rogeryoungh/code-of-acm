#pragma once
#include "../base.hpp"
#include "./euler-sieve.hpp"

// #region snippet
auto factor(i64 n) {
	std::vector<i64> ans;
	for (int i : primes) {
		if (1ll * i * i > n)
			break;
		for (; n % i == 0; n /= i)
			ans.push_back(i);
	}
	if (n > 1)
		ans.push_back(n);
	return ans;
}
// #endregion snippet
