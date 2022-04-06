#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 500000 + 10;

vector<int> G[N];

struct LCA {
    using T = std::array<int, 18>;
	vector<T> f;
    vector<int> dep;
	LCA(int n, int s) : dep(n) {
        f.resize(n);
        dfs(s, 0);
	}
	void dfs(int i, int fa) {
		f[i][0] = fa;
		dep[i] = dep[fa] + 1;
		for (int j = 1; j <= 18 - 1; j++) {
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
		for (auto v : G[i]) {
			if (v != fa)
				dfs(v, i);
		}
	}
	int query(int x, int y) {
		if (dep[x] < dep[y])
			swap(x, y);
		while (dep[x] > dep[y])
			x = f[x][0];
		if (x == y)
			return x;
		for (int k = 18 - 1; k >= 0; k--) {
			if (f[x][k] != f[y][k])
				x = f[x][k], y = f[y][k];
		}
		if (x == y)
			return x;
		return f[x][0];
	}
};

int main() {
	int n, m, s;
	cin >> n >> m >> s;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	LCA lca(n + 1, s);
	while (m--) {
		int x, y;
		cin >> x >> y;
		cout << lca.query(x, y) << "\n";
	}

	return 0;
}
