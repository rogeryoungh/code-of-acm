#include "basic/index.hpp"

#include "math/sieve/euler-lpf.cpp"

// @description 质因子分解

auto factor(ll n) {
	vector<ll> ret;
	for (; n > 1; n /= lpf[n])
		ret.push_back(lpf[n]);
	return ret;
}

#include "math/factor/factor-pii.cpp"
