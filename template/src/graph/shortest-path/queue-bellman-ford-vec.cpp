#include "basic/index.hpp"

#include "graph/saving/vec.cpp"

// @description 队列优化 Bellman Ford 最短路

template <class D>
auto queue_bellman_ford(const Graph<D> &G, int s) {
	int n = G.size();
	queue<int> q;
	vector<D> dis(n, std::numeric_limits<D>::max() / 2);
	vector<int> from(n, -1);
	dis[s] = 0, from[s] = s;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto [v, w] : G[u]) {
			int d2 = dis[u] + w;
			if (dis[v] > d2)
				dis[v] = d2, from[v] = u, q.push(v);
		}
	}
	return make_pair(dis, from);
}