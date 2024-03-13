
#pragma once
#include "../base.hpp"

// #region snippet
template <class T>
auto v2pti(std::span<const T> v) {
	std::vector<std::pair<T, int>> r;
	for (int i = 1; i < v.size(); i++) {
		if (i > 0 && v[i] == v[i - 1])
			r.back().second++;
		else
			r.emplace_back(v[i], 1);
	}
	return r;
}
// #endregion snippet
