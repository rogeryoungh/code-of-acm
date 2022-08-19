#include "basic/index.hpp"

// @description 扩展欧几里得

tuple<ll, ll, ll> exgcd(ll a, ll b) {
	if (b == 0) {
		ll s = a >= 0 ? 1 : -1;
		return {s, 0, a * s};
	} else {
		auto [y, x, g] = exgcd(b, a % b);
		return {x, y - a / b * x, g};
	}
}

ll inv_gcd(ll a, ll p) {
	return (get<0>(exgcd(a, p)) % p + p) % p;
}
