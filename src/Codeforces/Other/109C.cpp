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

using pib = pair<int, bool>;
vector<pib> G[N];

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		w = isluck(w);
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	vector<int> r;
	std::function<int(int, int)> dfs = [&](int u, int fa) {
		int sum = 0;
		for (auto [v, w] : G[u]) {
			if (v != fa) {
				int x = dfs(v, u);
				if (w) {
					r.push_back(x);
				} else {
					sum += x;
				}
			}
		}
		return sum + 1;
	};

	r.push_back(dfs(1, -1));

	ll ans = 0;
	for (auto sz : r) {
		int other = n - sz;
		ans += 1ll * sz * other * (other - 1);
	}

	cout << ans;

	return 0;
}
