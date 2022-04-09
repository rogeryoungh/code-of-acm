#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 1E5 + 10;
using pii = pair<int, int>;
vector<pii> G1[N], G2[N];

template <class T>
auto bellman_ford(int n, int s, const T &G) {
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

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G1[u].push_back({v, w});
		G2[v].push_back({u, w});
	}
	auto dis1 = bellman_ford(n, 1, G1);
	auto dis2 = bellman_ford(n, 1, G2);

	ll ans = 0;
	for (int i = 2; i <= n; i++) {
		ans += dis1[i] + dis2[i];
	}
	cout << ans;
	return 0;
}
