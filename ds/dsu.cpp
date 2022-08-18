#include <vector>
using namespace std;

// @problem https://judge.yosupo.jp/problem/unionfind

// @description 朴素并查集

struct DSU {
	vector<int> fa;
	DSU(int n) : fa(n) {
		for (int i = 0; i < n; i++)
			fa[i] = i;
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		fa[x] = y;
	}
};
