#pragma once
#include "../base.hpp"
#include "../base/vec2d.hpp"

// #region snippet
template <class D>
using Edges = vec2d<int>;

template <class D>
auto floyd(const Edges<D> &E) {
	int n = E.x;
	auto f = E;
	vec2d<int> pass(n, n, -1);
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				D d2 = f[i][k] + f[k][j];
				if (f[i][j] > d2)
					f[i][j] = d2, pass[i][j] = k;
			}
		}
	}
	return std::pair(f, pass);
}

auto get_path(const vec2d<int> &pass, int x, int y) {
	std::vector<int> path = {x};
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
// #endregion snippet

