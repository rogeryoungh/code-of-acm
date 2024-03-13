#pragma once
#include "../base.hpp"

// #region snippet
std::array<i64, 3> exgcd(i64 a, i64 b) {
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

i64 inv_gcd(i64 a, i64 p) {
	return (exgcd(a, p)[0] % p + p) % p;
}
// #endregion snippet
