#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

const int N = 10 + 5;

int f[N][N], dp[N * 2][N][N];

int main() {
	int n;
	std::cin >> n;
	while (true) {
		int a, b, c;
		std::cin >> a >> b >> c;
		if (a + b + c == 0) {
			break;
		}
		f[a][b] = c;
	}
	for (int s = 2; s <= n + n; ++s) {
		for (int i = std::max(s - n, 1); i <= std::min(s, n); ++i) {
			for (int j = std::max(s - n, 1); j <= std::min(s, n); ++j) {
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
	std::cout << dp[n + n][n][n];
	return 0;
}
