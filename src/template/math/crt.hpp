#pragma once
#include "../base.hpp"

// #region snippet
template <class T>
i64 crt(std::span<const T> a, std::span<const T> m) {
	assert(a.size() == m.size());
	i64 prod = 1, ret = 0;
	for (auto mi : m)
		prod *= mi;
	for (int i = 0; i < a.size(); ++i) {
		i64 u = prod / m[i], v = inv_gcd(u, m[i]);
		ret = (ret + a[i] * u * v) % prod;
	}
	return ret;
}
// #endregion snippet
