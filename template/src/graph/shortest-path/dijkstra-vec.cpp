#include "basic/index.hpp"

#include "graph/saving/vec.cpp"

// @description Dijkstra 最短路

template <class D>
auto dijkstra(const Edges<D> &E, int s) {
	int n = E.size();
	V<D> dis(n, std::numeric_limits<D>::max() / 2);
	V<int> from(n, -1);
	V<bool> vis(n);
	dis[s] = 0, from[s] = s;
	using pdi = std::pair<D, int>;
	std::priority_queue<pdi, V<pdi>, std::greater<pdi>> pq;
	pq.emplace(0, s);
	while (!pq.empty()) {
		auto [w, u] = pq.top();
		pq.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (auto [v, wi] : E[u]) {
			D d2 = w + wi;
			if (dis[v] > d2)
				dis[v] = d2, from[v] = u, pq.emplace(d2, v);
		}
	}
	return make_pair(dis, from);
}

auto get_path(const V<int> &from, int x, int y) {
	V<int> r;
	for (; x != y; y = from[y])
		r.push_back(y);
	r.push_back(y);
	std::reverse(r.begin(), r.end());
	return r;
}
