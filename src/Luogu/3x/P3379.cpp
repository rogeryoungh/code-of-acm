#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 500000 + 10;

vector<int> G[N];

template <int V, int U = 20>
struct LCA {
	vector<int> dep;
	inline static int f[V][U];
	LCA(int n, int s) : dep(n) {
		dfs(s, 0);
		for (int j = 1; j < U; j++) {
			for (int i = 1; i <= n; i++) {
				f[i][j] = f[f[i][j - 1]][j - 1];
			}
		}
	}
	void dfs(int i, int fa) {
		for (auto v : G[i]) {
			if (v != fa) {
				f[v][0] = i;
				dep[v] = dep[i] + 1;
				dfs(v, i);
			}
		}
	}
	int query(int x, int y) {
		if (dep[x] < dep[y])
			swap(x, y);
		while (dep[x] > dep[y])
			x = f[x][std::__lg(dep[x] - dep[y])];
		if (x == y)
			return x;
		for (int k = U - 1; k >= 0; k--) {
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
	LCA<N> lca(n + 1, s);
	while (m--) {
		int x, y;
		cin >> x >> y;
		cout << lca.query(x, y) << "\n";
	}

	return 0;
}
