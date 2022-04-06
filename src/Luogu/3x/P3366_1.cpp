#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

struct DSU {
	vector<int> fa;
	DSU(int n) : fa(n) {
		for (int i = 0; i < n; i++)
			fa[i] = i;
	}
	int find(int x) {
		if (fa[x] == x)
			return x;
		return fa[x] = find(fa[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		fa[x] = y;
	}
};

using Edge = tuple<int, int, int>;

vector<Edge> G;

int kruskal(int n) {
	sort(G.begin(), G.end(), [](Edge a, Edge b) {
		return std::get<2>(a) < std::get<2>(b);
	});
	ll ans = 0, cnt = 0;
	DSU dsu(n + 1);
	for (auto [u, v, w] : G) {
		int x = dsu.find(u), y = dsu.find(v);
		if (x == y) {
			continue;
		}
		ans += w;
		dsu.merge(x, y);
		cnt++;
		if (cnt == n - 1) {
			return ans;
		}
	}
	return -1;
}

int main() {
	int n, m;
	cin >> n >> m;
	G.reserve(m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G.push_back({u, v, w});
	}
	int ret = kruskal(n);
	if (ret == -1) {
		cout << "orz";
	} else {
		cout << ret;
	}
	return 0;
}
