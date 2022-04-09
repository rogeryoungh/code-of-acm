#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 1E3 + 10;
using pii = pair<int, int>;
int G1[N][N], G2[N][N];

template <class T>
auto bellman_ford(int n, int s, const T &G) {
	vector<int> dis(n + 1, 1E9);
	vector<char> vis(n + 1);
	dis[s] = 0;
	for (int k = 1; k < n; k++) {
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int d2 = dis[i] + G[i][j];
				if (d2 < dis[j]) {
					dis[j] = d2, flag = false;
				}
			}
		}
		if (flag)
			break;
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
	auto dis1 = bellman_ford(n, 1, G1);
	auto dis2 = bellman_ford(n, 1, G2);

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += dis1[i] + dis2[i];
	}
	cout << ans;
	return 0;
}