#pragma once
#include "../base.hpp"

// #region snippet
struct DSU {
	std::vector<int> fa;
	DSU(int n) : fa(n) {
		std::iota(fa.begin(), fa.end(), 0);
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	void merge(int x, int y) {
		fa[find(x)] = find(y);
	}
};
// #endregion snippet
