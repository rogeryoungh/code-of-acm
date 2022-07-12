#include <bits/stdc++.h>

using ll = long long;
using std::cin, std::cout, std::vector;
const char endl = '\n';

int ____ = cin.tie(0)->sync_with_stdio(0);

// END OF HEADER | Author: Roger Young

const int N = 1E3 + 10;
using pii = std::pair<int, int>;

std::vector<pii> G1[N], G2[N];

template <class T>
auto queue_bellman_ford(int n, int s, const T &G) {
	std::queue<int> q;
	vector<int> dis(n + 1, 1E9);
	dis[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int i = q.front();
		q.pop();
		for (auto [v, w] : G[i]) {
			int d2 = dis[i] + w;
			if (d2 < dis[v]) {
				dis[v] = d2;
				q.push(v);
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
	auto d1 = queue_bellman_ford(n, 1, G1);
	auto d2 = queue_bellman_ford(n, 1, G2);
	ll sum = 0;
	for (int i = 2; i <= n; i++) {
		sum += d1[i] + d2[i];
	}
	cout << sum;
	return 0;
}
