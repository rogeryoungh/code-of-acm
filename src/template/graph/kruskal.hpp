#pragma once
#include "../base.hpp"
#include "../datastruct/dsu.hpp"

// #region snippet
#include <algorithm>

using Edge = std::tuple<int, int, i64>;

i64 kruskal(std::vector<Edge> G, int n) {
	std::sort(G.begin(), G.end(), [](Edge a, Edge b) {
		return std::get<2>(a) < std::get<2>(b);
	});
	i64 ans = 0, cnt = 0;
	DSU dsu(n + 1);
	for (auto [u, v, w] : G) {
		if (dsu.find(u) == dsu.find(v)) {
			continue;
		}
		ans += w, cnt++;
		dsu.merge(u, v);
		if (cnt == n - 1) {
			return ans;
		}
	}
	return -1;
}
// #endregion snippet
