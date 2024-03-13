#pragma once
#include "../base.hpp"
#include "../using/using-i128.hpp"

// #region snippet
i64 qpow64(i64 a, i64 n, i64 m) {
	i64 ret = 1 % m;
	for (; n; n /= 2) {
		if (n & 1)
			ret = i128(a) * ret % m;
		a = i128(a) * a % m;
	}
	return ret;
}
// #endregion snippet
