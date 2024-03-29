#include "basic/index.hpp"

const int N = 1E5 + 5;
std::vector<std::vector<int>> G(N);

// @problem https://www.luogu.com.cn/problem/P3379

// @description 树链剖分 LCA

struct HLD {
	std::vector<int> sz, dep, fa, son, top, dfn;
	int cnt = 0;
	HLD(int n, int r = 1) : sz(n), dep(n), fa(n), son(n), top(n), dfn(n) {
		dfs1(r), dfs2(r, r);
	}
	void dfs1(int u, int f = 0) {
		dep[u] = dep[f] + 1;
		fa[u] = f, sz[u] = 1, top[u] = u;
		for (int v : G[u]) {
			if (v != f) {
				dfs1(v, u);
				sz[u] += sz[v];
				if (sz[v] > sz[son[u]]) {
					son[u] = v;
				}
			}
		}
	}
	void dfs2(int u, int tp, int f = 0) {
		top[u] = tp, dfn[u] = ++cnt;
		if (son[u] != 0) {
			dfs2(son[u], tp, u);
			for (int v : G[u]) {
				if (v != f && v != son[u]) {
					dfs2(v, v, u);
				}
			}
		}
	}
	int qpath(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] > dep[top[y]]) {
				std::swap(x, y);
			}
			y = fa[top[y]];
		}
		return dep[x] < dep[y] ? x : y;
	}
};
