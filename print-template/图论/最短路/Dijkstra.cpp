auto dijkstra(int n, int s) {
	vector<int> dis(n + 1, 1E9);
	vector<char> vis(n + 1);
	dis[s] = 0;
	priority_queue<pii, vector<pii>, std::greater<pii>> pq;
	pq.push({0, s});
	while (!pq.empty()) {
		auto [w, u] = pq.top();
		pq.pop();
		if (vis[u]) {
			continue;
		}
		vis[u] = true;
		for (auto [v, wi] : G[u]) {
			int len = w + wi;
			if (len < dis[v]) {
				dis[v] = len;
				pq.push({len, v});
			}
		}
	}
	return dis;
}
