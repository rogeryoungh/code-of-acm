#include "basic/index.hpp"

#include "basic/v2pti.hpp"

// @description 因式分解

auto factor(ll n) {
	std::vector<ll> ret;
	for (int i = 2; 1ll * i * i <= n; i++) {
		for (; n % i == 0; n /= i)
			ret.push_back(i);
	}
	if (n > 1)
		ret.push_back(n);
	return ret;
}
