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
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		fa[x] = y;
	}
};
