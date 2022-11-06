#include "basic/index.hpp"

#include "math/sieve/euler.cpp"

// @description 质因子分解

auto factor(ll n) {
	V<ll> ans;
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

#include "math/factor/factor-pii.cpp" // !!only
