#pragma once
#include "../base.hpp"
#include "../base/vec2d.hpp"

// #region snippet
template <class T, auto merge = std::plus()>
struct SparseTable {
	uint n, lgn;
	vec2d<T> v;
	SparseTable(std::span<const T> o) : n(o.size()), lgn(std::bit_width(n)), v(lgn, n) {
		std::ranges::copy(o, v[0]);
		for (int i = 1; i < lgn; i++) {
			for (int j = 0; j <= n - (1 << i); j++) {
				v[i][j] = merge(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	T query(int l, int r) const {
		int s = std::bit_width<uint>(r - l) - 1;
		return merge(v[s][l], v[s][r - (1 << s)]);
	}
};
// #endregion snippet
