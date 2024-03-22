#pragma once
#include "../base.hpp"

// #region snippet
template <class D>
using Edges = std::vector<std::vector<std::pair<int, D>>>;

template <class D>
auto bellman_ford(const Edges<D> &E, int s) {
	int n = E.size();
	std::vector<D> dis(n, std::numeric_limits<D>::max() / 2);
	std::vector<int> from(n, -1);
	dis[s] = 0, from[s] = s;
	bool flag = true;
	for (int k = 0; k < n && flag; k++) {
		flag = false;
		for (int u = 0; u < n; u++) {
			for (auto [v, w] : E[u]) {
				int d2 = dis[u] + w;
				if (dis[v] > d2)
					dis[v] = d2, from[v] = u, flag = true;
			}
		}
	}
	return std::pair(dis, from);
}
// #endregion snippet
