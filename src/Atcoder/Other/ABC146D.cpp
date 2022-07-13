// Problem: D - Coloring Edges on Tree
// URL: https://atcoder.jp/contests/abc146/tasks/abc146_d

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int N = 1E5 + 5;
vector<pair<int, int>> G[N];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back({v, i});
		G[v].push_back({u, i});
	}
	vector<int> color(n + 1), cans(n + 1);
	int k = 1;
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		int ci = 1;
		for (auto [v, i] : G[u]) {
			if (v != fa) {
				if (color[u] == ci) {
					ci++;
				}
				color[v] = ci;
				cans[i] = ci;
				ci++;
				dfs(v, u);
			}
		}
		k = max(k, ci - 1);
	};
	color[1] = 0;
	dfs(1, 0);
	cout << k << endl;
	for (int i = 1; i < n; i++) {
		cout << cans[i] << endl;
	}
	return 0;
}
