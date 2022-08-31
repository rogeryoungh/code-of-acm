#include "basic/index.hpp"

#include "graph/saving/adj.cpp"

// @description Floyd 最短路

template <class D>
auto floyd(const Graph<D> &G) {
	int n = G.x;
	auto f = G;
	VV<int> pass(n, n, -1);
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				D d2 = f[i][k] + f[k][j];
				if (f[i][j] > d2)
					f[i][j] = d2, pass[i][j] = k;
			}
		}
	}
	return make_pair(f, pass);
}

auto get_path(const VV<int> &pass, int x, int y) {
	vector<int> path = {x};
	std::function<void(int, int)> dfs = [&](int a, int b) {
		if (pass[a][b] != -1) {
			int p = pass[a][b];
			dfs(a, p), path.push_back(p), dfs(p, b);
		}
	};
	if (x != y)
		dfs(x, y), path.push_back(y);
	return path;
}
