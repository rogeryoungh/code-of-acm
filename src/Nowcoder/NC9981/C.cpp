#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young


const int N = 1E5;

vector<int> G[N];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	vector<int> vis(n + 1), col(n + 1);
	int cnt = 0;
	std::function<void(int, int)> dfs1 = [&](int x, int fa) {
		for (auto u : G[x]) {
			if (u != fa)
				dfs1(u, x);
		}
		if (!vis[x]) {
			if (vis[fa]) {
				cout << "-1";
				exit(0);
			}
			vis[fa] = vis[x] = ++cnt;
		}
	};

	std::function<void(int, int)> dfs2 = [&](int x, int fa) {
		for (auto u : G[x]) {
			if (u == fa)
				continue;
			if (vis[u] == vis[x]) {
				col[u] = col[x];
			} else {
				col[u] = !col[x];
			}
			dfs2(u, x);
		}
	};

	vis[0] = 1, col[1] = 1;
	dfs1(1, 0), dfs2(1, 0);

	for (int i = 1; i <= n; i++) {
		cout << (col[i] ? 'R' : 'B');
	}

	return 0;
}
