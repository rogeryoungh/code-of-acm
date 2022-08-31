#include "basic/index.hpp"

#include "graph/saving/vec.cpp"

// @description Dijkstra 最短路

template <class D>
auto dijkstra(const Graph<D> &G, int s) {
	int n = G.size();
	vector<D> dis(n, std::numeric_limits<D>::max() / 2);
	vector<int> from(n, -1);
	vector<bool> vis(n);
	dis[s] = 0, from[s] = s;
	using pdi = pair<D, int>;
	priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
	pq.emplace(0, s);
	while (!pq.empty()) {
		auto [w, u] = pq.top();
		pq.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (auto [v, wi] : G[u]) {
			D d2 = w + wi;
			if (dis[v] > d2)
				dis[v] = d2, from[v] = u, pq.emplace(d2, v);
		}
	}
	return make_pair(dis, from);
}

auto get_path(const vector<int> &from, int x, int y) {
	vector<int> ret;
	for (; x != y; y = from[y])
		ret.push_back(y);
	ret.push_back(y);
	reverse(ret.begin(), ret.end());
	return ret;
}
