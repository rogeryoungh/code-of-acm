#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> v(m);
	for (auto &vi : v)
		cin >> vi;
	ll ans = 0;
	for (int i = 0; i < m - 1; i++) {
		ans += abs(v[i] - v[i + 1]);
	}

	vector<vector<int>> e(n + 1);
	for (int i = 0; i < m; i++) {
		if (i > 0 && v[i - 1] != v[i])
			e[v[i]].push_back(v[i - 1]);
		if (i < m - 1 && v[i + 1] != v[i])
			e[v[i]].push_back(v[i + 1]);
	}

	ll sum = 0;
	for (int i = 1; i <= n; i++) {
		if (e[i].empty())
			continue;
		sort(e[i].begin(), e[i].end());
		int mid = e[i][(e[i].size() - 1) / 2];
		ll s1 = 0, s2 = 0;
		for (auto eii : e[i]) {
			s1 += abs(mid - eii);
			s2 += abs(i - eii);
		}
		sum = max(sum, s2 - s1);
	}

	cout << ans - sum;
	return 0;
}
