#include <bits/stdc++.h>
#include <boost/stacktrace.hpp>
#include <csignal>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int N = 2E5 + 10;
vector<int> G[N];
ll sz[N], ans[N], dp[N], a[N];

ll cal(ll x) {
	return (x + 1) * x / 2;
}

void dfs(int x, int fa) {
	int col = a[x];
	int now = dp[col];
	sz[x] = 1;
	for (int i : G[x]) {
		if (i == fa)
			continue;
		int pre = dp[col];
		dfs(i, x);
		int diff = dp[col] - pre;
		sz[x] += sz[i];
		ans[col] += cal(sz[i] - diff);
	}

	dp[col] = now + sz[x];
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) {
		ll res = cal(n) - cal(n - dp[i]) - ans[i];
		cout << res << endl;
	}
	int *p = nullptr;
	*p = 1;
	std::signal(SIGSEGV, [](int sig) {
		// cerr << boost::stacktrace::stacktrace() << endl;
		exit(0);
	});
	return 0;
}
