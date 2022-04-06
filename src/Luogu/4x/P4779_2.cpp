#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

using pii = pair<int, int>;

struct SCC {
	vector<pii> G;
	vector<int> head, next;
    int cnt = 0;
	void init(int n, int m) {
        n++, m++;
		head.resize(n);
		next.resize(m);
		G.resize(m);
	}
	void add(int u, int v, int w) {
        G[++cnt] = {v, w};
		next[cnt] = head[u];
		head[u] = cnt;
	}
	auto get(int u) {
		vector<pii> ret;
        u = head[u];
		while (u) {
		    ret.push_back(G[u]);
			u = next[u];
		}
		return ret;
	}
};

SCC G;

auto dijkstra(int n, int s) {
	vector<int> dis(n + 1, 1E9);
	vector<char> vis(n + 1);
	dis[s] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, s});
	while (!pq.empty()) {
		auto [w, u] = pq.top();
		pq.pop();
		if (vis[u]) {
			continue;
		}
		vis[u] = true;
		for (auto [v, wi] : G.get(u)) {
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
	int n, m, s;
	cin >> n >> m >> s;
	G.init(n, m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G.add(u, v, w);
	}
	auto dis = dijkstra(n, s);
	for (int i = 1; i <= n; i++) {
		cout << dis[i] << " \n"[i == n];
	}
	return 0;
}
