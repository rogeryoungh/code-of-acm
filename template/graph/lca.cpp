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
		f[i][0] = fa;
		dep[i] = dep[fa] + 1;
		for (auto v : G[i]) {
			if (v != fa)
				dfs(v, i);
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
