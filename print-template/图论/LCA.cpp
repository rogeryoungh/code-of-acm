struct LCA {
	const int lgn;
	VV<int> f;
	vector<int> dep;
	LCA(int n, int s = 1) : lgn(1 + std::__lg(n)), f(n, lgn), dep(n) {
		dfs(s, 0);
		for (int i = 1; i < lgn; i++) {
			for (int j = 0; j < n; j++) {
				f[j][i] = f[f[j][i - 1]][i - 1];
			}
		}
	}
	void dfs(int x, int fa) {
		f[x][0] = fa;
		dep[x] = dep[fa] + 1;
		for (int u : G[x]) {
			if (u != fa) {
				dfs(u, x);
			}
		}
	}
	int query(int x, int y) {
		if (dep[x] > dep[y])
			swap(x, y);
		while (dep[x] < dep[y]) {
			y = f[y][std::__lg(dep[y] - dep[x])];
		}
		for (int i = lgn - 1; i >= 0; i--) {
			if (f[x][i] != f[y][i]) {
				x = f[x][i], y = f[y][i];
			}
		}
		return x == y ? x : f[x][0];
	}
};
