#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

template <class D>
struct Edge {
	int to;
	D len;
};

template <class D>
using Edges = std::vector<std::vector<Edge<D>>>;

// @description Dijkstra 最短路

template <class D>
auto dijkstra(const Edges<D> &E, int s) {
	int n = E.size();
	std::vector<D> dis(n, std::numeric_limits<D>::max() / 2);
	std::vector<int> from(n, -1);
	std::vector<bool> vis(n);
	using pdi = std::tuple<D, int, int>;
	std::priority_queue<pdi, std::vector<pdi>, std::greater<pdi>> pq;
	pq.emplace(0, s, s);
	while (!pq.empty()) {
		auto [w, u, v] = pq.top();
		pq.pop();
		if (vis[v])
			continue;
		dis[v] = w, from[v] = u;
		vis[v] = true;
		for (auto [vi, wi] : E[v]) {
			D d2 = w + wi;
			if (dis[vi] > d2)
				pq.emplace(d2, v, vi);
		}
	}
	return std::make_pair(dis, from);
}

int main() {
	int n, m, s;
	std::cin >> n >> m >> s;
	Edges<int> G(n + 1);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].push_back({v, w});
	}
	auto [dis, from] = dijkstra(G, s);
	for (int i = 1; i <= n; i++)
		std::cout << (from[i] != -1 ? dis[i] : 0x7fffffff) << ' ';
}
