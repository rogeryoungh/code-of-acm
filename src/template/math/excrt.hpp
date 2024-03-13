#pragma once
#include "../base.hpp"
#include "./exgcd.hpp"
#include "../using/using-i128.hpp"

// #region snippet
template <class T>
i64 excrt(std::span<const T> a, std::span<const T> m) {
	assert(a.size() == m.size());
	i64 ans = a[0], M = m[0];
	for (int i = 0; i < a.size(); ++i) {
		i64 ai = a[i], mi = m[i];
		if (M % mi == 0 && ans % mi == a)
			continue;
		i64 B = (ai - ans % mi + mi) % mi;
		auto [x, y, g] = exgcd(M, mi);
		if (B % g != 0)
			return -1;
		x = i128(x) * (B / g) % (mi / g);
		ans += M * x, M *= mi / g;
		ans = (ans + M) % M;
	}
	return ans;
}
// #endregion snippet
