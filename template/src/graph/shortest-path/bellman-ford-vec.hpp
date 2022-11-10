#include "basic/index.hpp"

#include "graph/saving/vec.hpp"

// @description Bellman Ford 最短路

template <class D>
auto bellman_ford(const Edges<D> &E, int s) {
	int n = E.size();
	V<D> dis(n, std::numeric_limits<D>::max() / 2);
	V<int> from(n, -1);
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
	return std::make_pair(dis, from);
}
