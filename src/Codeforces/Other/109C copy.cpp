#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

bool isluck(int n) {
	while (n != 0) {
		int m = n % 10;
		if (m != 4 && m != 7) {
			return false;
		}
		n /= 10;
	}
	return true;
}

const int N = 1E5 + 5;
vector<int> G[N];

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

int main() {
	int n;
	cin >> n;

	DSU dsu(n + 1);

	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		w = isluck(w);
		if (!w) {
			dsu.merge(u, v);
		}
		G[u].push_back(v);
		G[v].push_back(u);
	}

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		if (dsu.find(i) != i) {
			continue;
		}
		int other = n - dsu.size(i);
		ans += 1ll * dsu.size(i) * other * (other - 1);
	}

	cout << ans;

	return 0;
}
