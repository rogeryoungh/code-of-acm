#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

auto i2v(ll x) {
	vector<int> v;
	while (x > 0) {
		v.push_back(x % 10);
		x /= 10;
	}
	std::reverse(v.begin(), v.end());
	return v;
}

// i x limit
ll dp[20][10][2];

ll solve(ll n) { // 0~n-1
	memset(dp, 0, sizeof(dp));
	auto v = i2v(n);
	for (int i = 0; i < v.size(); i++) {
		for (int x = 1; x <= (i == 0 ? v[i] : 9); x++) {
			dp[i + 1][x][i == 0 && x == v[i]] += 1;
		}
		for (int y = 0; y <= 9; y++) {
			for (int s : {0, 1}) {
				for (int x = 0; x <= (s ? v[i] : 9); x++) {
					if (std::abs(x - y) >= 2) {
						dp[i + 1][x][s && x == v[i]] += dp[i][y][s];
					}
				}
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i <= 9; i++) {
		ans += dp[v.size()][i][0];
		ans += dp[v.size()][i][1];
	}
	return ans;
}

int main() {
	ll l, r;
	cin >> l >> r;
	cout << solve(r) - solve(l - 1);
	return 0;
}
