#include <vector>
using namespace std;

// @description 朴素并查集
// @problem https://judge.yosupo.jp/problem/unionfind

struct DSU {
	vector<int> fa;
	DSU(int n) : fa(n) {
		for (int i = 0; i < n; i++)
			fa[i] = i;
	}
	int leader(int x) {
		return fa[x] == x ? x : fa[x] = leader(fa[x]);
	}
	bool same(int x, int y) {
		return leader(x) == leader(y);
	}
	void merge(int x, int y) {
		x = leader(x), y = leader(y);
		fa[x] = y;
	}
};
