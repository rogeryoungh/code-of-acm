int kruskal(int n) {
	sort(G.begin(), G.end(), [](Edge a, Edge b) {
		return std::get<2>(a) < std::get<2>(b);
	});
	ll ans = 0, cnt = 0;
	DSU dsu(n + 1);
	for (auto [u, v, w] : G) {
		int x = dsu.find(u), y = dsu.find(v);
		if (x == y) {
			continue;
		}
		ans += w;
		dsu.merge(x, y);
		cnt++;
		if (cnt == n - 1) {
			return ans;
		}
	}
	return -1;
}
