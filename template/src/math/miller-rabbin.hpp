#include "basic/index.hpp"

#include "basic/qpow/qpow128.hpp"

// @description 素性测试(Miller Rabbin)

bool miller_rabbin(ll n) {
	if (n <= 3)
		return n >= 2;
	if (n % 2 == 0)
		return false;
	ll a = n - 1;
	a /= a & -a;
	for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
		if (n <= p)
			return true;
		ll t = a, v = qpow128(p, t, n);
		while (t != n - 1 && v != 1 && v != n - 1)
			v = i128(v) * v % n, t *= 2;
		if (v != n - 1 && t % 2 == 0)
			return false;
	}
	return true;
}
