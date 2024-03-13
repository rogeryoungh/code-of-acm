#pragma once
#include "../base.hpp"
#include "../base/qpow64.hpp"
#include "./is-prime-small.hpp"

// #region snippet
bool miller_rabin(i64 n) {
	if (!is_prime_small(n))
		return false;
	i64 a = n - 1;
	a /= a & -a;
	for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
		if (n <= p)
			return true;
		i64 t = a, v = qpow64(p, t, n);
		while (t != n - 1 && v != 1 && v != n - 1)
			v = i128(v) * v % n, t *= 2;
		if (v != n - 1 && t % 2 == 0)
			return false;
	}
	return true;
}
// #endregion snippet
