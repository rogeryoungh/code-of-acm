#include "basic/index.hpp"

#include "graph/saving/vec.cpp"

// @description Bellman Ford 最短路

template <class D>
auto bellman_ford(const Graph<D> &G, int s) {
	int n = G.size();
	vector<D> dis(n, std::numeric_limits<D>::max() / 2);
	vector<int> from(n, -1);
	dis[s] = 0, from[s] = s;
	bool flag = true;
	for (int k = 0; k < n && flag; k++) {
		flag = false;
		for (int u = 0; u < n; u++) {
			for (auto [v, w] : G[u]) {
				int d2 = dis[u] + w;
				if (dis[v] > d2)
					dis[v] = d2, from[v] = u, flag = true;
			}
		}
	}
	return make_pair(dis, from);
}