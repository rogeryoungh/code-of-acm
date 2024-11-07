#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

const int N = 50 + 5;

int f[N][N], dp[N * 2][N][N];

int main() {
	int n, m;
	std::cin >> m >> n;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			std::cin >> f[i][j];
		}
	}
	for (int s = 2; s <= n + m; ++s) {
		for (int i = std::max(s - n, 1); i <= std::min(s, m); ++i) {
			for (int j = std::max(s - n, 1); j <= std::min(s, m); ++j) {
				auto &g = dp[s - 1];
				int x = std::max({g[i - 1][j - 1], g[i - 1][j], g[i][j - 1], g[i][j]});
				if (i != j) {
					dp[s][i][j] = x + f[i][s - i] + f[j][s - j];
				} else {
					dp[s][i][j] = x + f[i][s - i];
				}
			}
		}
	}
	std::cout << dp[n + m][m][m];
	return 0;
}
