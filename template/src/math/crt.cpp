#include "basic/index.hpp"

#include "math/exgcd.cpp"

// @description 中国剩余定理

template <class PAIR>
ll crt(const V<PAIR> &am) {
	ll prod = 1, ret = 0;
	for (auto [a, m] : am)
		prod *= m;
	for (auto [a, m] : am) {
		ll u = prod / m, v = inv_gcd(u, m);
		ret = (ret + a * u * v) % prod;
	}
	return ret;
}
