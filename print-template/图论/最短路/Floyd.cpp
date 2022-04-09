void floyd(int n) {
	memcpy(dis, G, sizeof(dis));
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			if (i == k || dis[i][k] == 0x3f3f3f3f)
				continue;
			for (int j = 1; j <= n; j++) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
}