#pragma once
#include "../base.hpp"

// #region snippet
i64 floor_sum(i64 a, i64 b, i64 c, i64 n) {
	i64 m = (a * n + b) / c, S1 = n * (n + 1) / 2;
	if (a == 0) {
		return b / c * (n + 1);
	} else if (a >= c || b >= c) {
		i64 f = S1 * (a / c) + b / c * (n + 1);
		return f + floor_sum(a % c, b % c, c, n);
	} else {
		return m * n - floor_sum(c, c - b - 1, a, m - 1);
	}
}
// #endregion snippet
