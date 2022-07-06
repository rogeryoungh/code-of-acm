ll kruskal(int n) {
	std::sort(G.begin(), G.end(), [](Edge a, Edge b) {
		return get<2>(a) < get<2>(b);
	});
	ll ans = 0, cnt = 0;
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
