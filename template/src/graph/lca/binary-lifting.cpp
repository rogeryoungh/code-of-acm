#include "basic/index.hpp"

#include "graph/saving/vec.cpp"

#include "basic/vec2.cpp"

// @description LCA(倍增)

struct LCA {
	const int n, lgn;
	VV<int> f;
	V<int> dep;
	LCA(int n_) : n(n_), lgn(1 + std::__lg(n)), f(n, lgn), dep(n) {}
	int query(int x, int y) {
		if (dep[x] > dep[y])
			std::swap(x, y);
		while (dep[x] < dep[y])
			y = f[y][std::__lg(dep[y] - dep[x])];
		for (int i = lgn - 1; i >= 0; i--) {
			if (f[x][i] != f[y][i]) {
				x = f[x][i], y = f[y][i];
			}
		}
		return x == y ? x : f[x][0];
	}
};

template <class D>
struct LCAImpl : LCA {
	const Edges<D> &E;
	LCAImpl(const Edges<D> &E_, int s = 1) : LCA(E_.size()), E(E_) {
		dfs(s, 0);
		for (int i = 1; i < lgn; i++) {
			for (int j = 0; j < n; j++) {
				f[j][i] = f[f[j][i - 1]][i - 1];
			}
		}
	}
	void dfs(int u, int fa) {
		f[u][0] = fa;
		dep[u] = dep[fa] + 1;
		for (auto e : E[u]) {
			if (e.to != fa) {
				dfs(e.to, u);
			}
		}
	}
};
