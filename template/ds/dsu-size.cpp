#include <vector>
using namespace std;

// @description 带权并查集
// https://www.luogu.com.cn/problem/P1536 也不是不能用

struct DSU {
	vector<int> fa, sz;
	DSU(int n) : fa(n), sz(n, 1) {
		for (int i = 0; i < n; i++)
			fa[i] = i;
	}
	int leader(int x) {
		return fa[x] == x ? x : fa[x] = leader(fa[x]);
	}
	bool same(int x, int y) {
		return leader(x) == leader(y);
	}
	int size(int x) {
		return sz[leader(x)];
	}
	void merge(int x, int y) {
		x = leader(x), y = leader(y);
		sz[y] += sz[x], fa[x] = y;
		sz[x] = 0;
	}
};
