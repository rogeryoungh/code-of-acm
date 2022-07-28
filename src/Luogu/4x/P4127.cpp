#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int N = 19;
ll dp[N][N * 11][N * 10][2];
// i s n%rem limit

auto i2v(ll x) {
	vector<int> v;
	while (x > 0) {
		v.push_back(x % 10);
		x /= 10;
	}
	std::reverse(v.begin(), v.end());
	return v;
}

ll solve(ll n, int rem) {
	auto v = i2v(n);
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < v.size(); i++) {
		for (int x = 1; x <= (i == 0 ? v[i] : 9); x++) {
			dp[i + 1][x][x % rem][i == 0 && x == v[i]] += 1;
		}
		for (int y = 0; y <= rem; y++) {
			for (int o = 0; o < rem; o++) {
				for (int x = 0; x <= v[i]; x++) {
					dp[i + 1][y + x][(o * 10 + x) % rem][x == v[i]] += dp[i][y][o][1];
				}
				for (int x = 0; x <= 9; x++) {
					dp[i + 1][y + x][(o * 10 + x) % rem][0] += dp[i][y][o][0];
				}
			}
		}
	}
	return dp[v.size()][rem][0][0] + dp[v.size()][rem][0][1];
}

int main() {
	ll l, r;
	cin >> l >> r;
	ll ans = 0;
	for (int i = 1; i <= N * 9; i++) {
		ans += solve(r, i) - solve(l - 1, i);
	}
	cout << ans;
	return 0;
}
