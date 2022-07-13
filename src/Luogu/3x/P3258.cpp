#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

using pii = pair<int, int>;

const int N = 3E5 + 10;
vector<int> G[N];

template <class T>
struct Mtx {
	int x, y;
	vector<T> m;
	Mtx(int a, int b) : x(a), y(b), m(a * b) {}
	auto operator[](int i) {
		return m.begin() + i * y;
	}
	auto operator[](int i) const {
		return m.begin() + i * y;
	}
};

struct LCA {
	const int lgn;
	Mtx<int> f;
	vector<int> dep;
	LCA(int n, int s = 1) : lgn(1 + std::__lg(n)), f(lgn, n), dep(n) {
		dfs(s, 0);
		for (int i = 1; i < lgn; i++) {
			for (int j = 0; j < n; j++) {
				f[i][j] = f[i - 1][f[i - 1][j]];
			}
		}
	}
	void dfs(int x, int fa) {
		f[0][x] = fa;
		dep[x] = dep[fa] + 1;
		for (auto u : G[x]) {
			if (u != fa) {
				dfs(u, x);
			}
		}
	}
	int query(int x, int y) {
		if (dep[x] > dep[y])
			swap(x, y);
		while (dep[x] < dep[y]) {
			y = f[std::__lg(dep[y] - dep[x])][y];
		}
		for (int i = lgn - 1; i >= 0; i--) {
			if (f[i][x] != f[i][y]) {
				x = f[i][x], y = f[i][y];
			}
		}
		return x == y ? x : f[0][x];
	}
};

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	LCA lca(n + 1);
	vector<int> pre(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int u = a[i], v = a[i + 1];
		int w = lca.query(u, a[i + 1]);
		pre[u]++, pre[w]--;
		pre[lca.f[0][v]]++, pre[lca.f[0][w]]--;
	}
	vector<int> ans(n + 1);
	std::function<int(int, int)> dfs = [&](int x, int fa) {
		int sum = pre[x];
		for (auto u : G[x]) {
			if (u != fa) {
				sum += dfs(u, x);
			}
		}
		ans[x] = sum;
		return sum;
	};
	dfs(1, 0);
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << endl;
	}
	return 0;
}
