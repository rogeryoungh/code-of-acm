#pragma once
#include "../base.hpp"

// #region snippet
auto factor(i64 n) {
	std::vector<i64> ret;
	for (int i = 2; i64(i) * i <= n; i++) {
		for (; n % i == 0; n /= i)
			ret.push_back(i);
	}
	if (n > 1)
		ret.push_back(n);
	return ret;
}
// #endregion snippet
