#include <bits/stdc++.h>

using ll = long long;
using std::cin, std::cout, std::vector;
const char endl = '\n';

int ____ = cin.tie(0)->sync_with_stdio(0);

// END OF HEADER | Author: Roger Young

using pii = std::pair<int, ll>;

std::vector<std::vector<pii>> G;

bool queue_bellman_ford(int n, int s) {
	std::queue<int> q;
	vector<ll> dis(n + 1, 1E15);
	vector<int> len(n + 1);
	dis[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int i = q.front();
		q.pop();
		if (len[i] >= n) {
			return true;
		}
		for (auto [v, w] : G[i]) {
			ll d2 = dis[i] + w;
			if (d2 < dis[v]) {
				len[v] = len[i] + 1;
				dis[v] = d2;
				q.push(v);
			}
		}
	}
	return false;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;
		G.clear();
		G.resize(n + 1);
		for (int i = 0; i < m; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			G[u].push_back({v, w});
			if (w >= 0) {
				G[v].push_back({u, w});
			}
		}
		auto ret = queue_bellman_ford(n, 1);
		cout << (ret ? "YES" : "NO") << endl;
	}
	return 0;
}
