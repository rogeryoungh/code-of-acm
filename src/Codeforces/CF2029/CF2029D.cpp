#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> cnt(n + 1);
	std::vector<std::array<int, 3>> ans;
	for (int i = 0; i < m; ++i) {
		int u, v;
		std::cin >> u >> v;
		if (u > v)
			std::swap(u, v);
		if (u == 1) {
			cnt[v] ^= 1;
		} else {
			ans.push_back({1, u, v});
			cnt[u] ^= 1;
			cnt[v] ^= 1;
		}
	}
	std::vector<int> s, ns;
	for (int i = 2; i <= n; ++i) {
		if (cnt[i])
			s.push_back(i);
		else
			ns.push_back(i);
	}
	if (!s.empty()) {
		int t = s[0];
		for (int j : ns) {
			ans.push_back({1, t, j});
			t = j;
		}
	}
	std::cout << ans.size() << '\n';
	for (auto [a, b, c] : ans) {
		std::cout << a << " " << b << " " << c << "\n";
	}
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
