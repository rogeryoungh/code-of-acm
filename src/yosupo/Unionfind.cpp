#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

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

int main() {
	int n, q;
	cin >> n >> q;
	DSU dsu(n);
	while (q--) {
		int t, u, v;
		cin >> t >> u >> v;
		if (t == 0) {
			dsu.merge(u, v);
		} else {
			bool ret = dsu.find(u) == dsu.find(v);
			cout << ret << endl;
		}
	}
	return 0;
}
