#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 1E3 + 10;
using pii = pair<int, int>;
int G1[N][N], G2[N][N];

template <class T>
auto dijkstra(int n, int s, const T &G) {
	vector<int> dis(n + 1, 1E9);
	vector<char> vis(n + 1);
	dis[s] = 0;
	for (int k = 1; k <= n; k++) {
		int mi = -1;
		for (int j = 1; j <= n; j++) {
			if (vis[j])
				continue;
			if (mi == -1 || dis[j] < dis[mi]) {
				mi = j;
			}
		}
		vis[mi] = true;
		for (int j = 1; j <= n; j++) {
			dis[j] = min(dis[j], dis[mi] + G[mi][j]);
		}
	}
	return dis;
}

int main() {
	int n, m;
	cin >> n >> m;
	memset(G1, 0x3f, sizeof(G1));
	memset(G2, 0x3f, sizeof(G2));
	for (int i = 1; i <= n; i++) {
		G1[i][i] = G2[i][i] = 0;
	}
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G1[u][v] = min(w, G1[u][v]);
		G2[v][u] = min(w, G2[v][u]);
	}
	auto dis1 = dijkstra(n, 1, G1);
	auto dis2 = dijkstra(n, 1, G2);

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += dis1[i] + dis2[i];
	}
	cout << ans;
	return 0;
}