#include <vector>
using namespace std;

// @description 带权并查集

struct DSU {
	vector<int> fa, sz;
	DSU(int n) : fa(n), sz(n, 1) {
		for (int i = 0; i < n; i++)
			fa[i] = i;
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	int size(int x) {
		return sz[x];
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		sz[y] += sz[x], fa[x] = y;
		sz[x] = 0;
	}
};
