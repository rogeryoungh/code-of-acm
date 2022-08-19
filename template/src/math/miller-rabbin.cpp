#include "intro/index.hpp"

using i128 = __int128_t;

// @problem https://loj.ac/p/143

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

// @description 素性测试(Miller Rabbin)

bool miller_rabbin(ll n) {
	if (n <= 3)
		return n >= 2;
	if (n % 2 == 0)
		return false;
	ll a = n - 1;
	while (a % 2 == 0)
		a /= 2;
	for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
		if (n <= p)
			return true;
		ll t = a, v = qpow128(p, t, n);
		while (t != n - 1 && v != 1 && v != n - 1) {
			v = i128(v) * v % n, t *= 2;
		}
		if (v != n - 1 && t % 2 == 0)
			return false;
	}
	return true;
}