#include "basic/index.hpp"

// @description 扩展欧几里得

std::tuple<ll, ll, ll> exgcd(ll a, ll b) {
	if (b == 0) {
		if (a > 0)
			return {1, 0, a};
		else
			return {-1, 0, -a};
	} else {
		auto [y, x, g] = exgcd(b, a % b);
		return {x, y - a / b * x, g};
	}
}

ll inv_gcd(ll a, ll p) {
	return (std::get<0>(exgcd(a, p)) % p + p) % p;
}
