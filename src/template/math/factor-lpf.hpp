#pragma once
#include "../base.hpp"
#include "./euler-sieve-lpf.hpp"

// #region snippet
auto factor(i64 n) {
	std::vector<i64> ret;
	for (; n > 1; n /= lpf[n])
		ret.push_back(lpf[n]);
	return ret;
}
// #endregion snippet
