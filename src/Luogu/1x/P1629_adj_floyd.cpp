#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 1E3 + 10;
using pii = pair<int, int>;
int G1[N][N], G2[N][N], dis[N][N];

template <class T>
void floyd(int n, const T &G) {
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

int main() {
	int n, m;
	cin >> n >> m;
	memset(G1, 0x3f, sizeof(G1));
	for (int i = 1; i <= n; i++) {
		G1[i][i] = G2[i][i] = 0;
	}
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G1[u][v] = min(w, G1[u][v]);
	}
	floyd(n, G1);

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += dis[1][i] + dis[i][1];
	}
	cout << ans;
	return 0;
}