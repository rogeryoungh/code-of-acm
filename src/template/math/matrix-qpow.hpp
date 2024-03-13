#pragma once
#include "../base.hpp"
#include "../base/vec2d.hpp"

// #region snippet
template <class T>
auto make_matrix_E(int n) {
	vec2d<T> ret(n, n);
	for (int i = 0; i < n; i++)
		ret[i][i] = 1;
	return ret;
}

template <class T>
auto matrix_pow(vec2d<T> a, i64 w) {
	auto ret = make_matrix_E<T>(a.x);
	for (; w > 0; w /= 2) {
		if (w & 1)
			ret = a * ret;
		a = a * a;
	}
	return ret;
}
// #endregion snippet
