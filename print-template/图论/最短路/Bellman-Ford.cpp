auto bellman_ford(int n, int s) {
	vector<int> dis(n + 1, 1E9);
	dis[s] = 0;
	for (int k = 1; k < n; k++) {
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			for (auto [v, w] : G[i]) {
				int d2 = dis[i] + w;
				if (d2 < dis[v]) {
					dis[v] = d2, flag = false;
				}
			}
		}
		if (flag)
			break;
	}
	return dis;
}
