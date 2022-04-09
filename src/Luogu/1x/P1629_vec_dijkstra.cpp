#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 1E5 + 10;
using pii = pair<int, int>;
vector<pii> G1[N], G2[N];

template <class T>
auto dijkstra(int n, int s, const T &G) {
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

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G1[u].push_back({v, w});
		G2[v].push_back({u, w});
	}
	auto dis1 = dijkstra(n, 1, G1);
	auto dis2 = dijkstra(n, 1, G2);

	ll ans = 0;
	for (int i = 2; i <= n; i++) {
		ans += dis1[i] + dis2[i];
	}
	cout << ans;
	return 0;
}
