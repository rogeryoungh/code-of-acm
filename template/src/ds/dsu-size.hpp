#include "basic/index.hpp"

// @description 带权并查集

struct DSU {
	std::vector<int> fa, sz;
	DSU(int n) : fa(n), sz(n, 1) {
		for (int i = 0; i < n; i++)
			fa[i] = i;
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	int size(int x) {
		return sz[find(x)];
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y)
			return;
		if (sz[x] > sz[y])
			std::swap(x, y);
		sz[y] += sz[x], fa[x] = y;
		sz[x] = 0;
	}
};
