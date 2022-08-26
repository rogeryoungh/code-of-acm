#include "basic/index.hpp"

using i128 = __int128_t;

// @description 快速幂(i128)

ll qpow128(ll a, ll b, ll m) {
	ll ret = m != 1;
	for (; b; b /= 2) {
		if (b % 2 == 1)
			ret = i128(ret) * a % m;
		a = i128(a) * a % m;
	}
	return ret;
}