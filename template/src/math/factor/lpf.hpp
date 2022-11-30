#include "basic/index.hpp"

#include "basic/v2pti.hpp"

#include "math/sieve/euler-lpf.hpp"

// @description 质因子分解

auto factor(ll n) {
	V<ll> ret;
	for (; n > 1; n /= lpf[n])
		ret.push_back(lpf[n]);
	return ret;
}
