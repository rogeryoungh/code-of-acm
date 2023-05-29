#include "basic/index.hpp"

// @description V<T> -> V<pair<T, count>>

template <class T>
auto v2pti(const std::vector<T> &v) {
	std::vector<std::pair<T, int>> r;
	if (v.empty())
		return r;
	r.emplace_back(v[0], 1);
	for (int i = 1; i < v.size(); i++) {
		if (v[i] == v[i - 1])
			r.back().second++;
		else
		 	r.emplace_back(v[i], 1);
	}
	return r;
}
