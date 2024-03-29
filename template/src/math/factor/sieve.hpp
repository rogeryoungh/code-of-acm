#include "basic/index.hpp"

#include "basic/v2pti.hpp"

#include "math/sieve/euler.hpp"

// @description 质因子分解

auto factor(ll n) {
	std::vector<ll> ans;
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
