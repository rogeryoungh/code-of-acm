#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

using i128 = __int128;

void print(i128 x) {
	if (x >= 10)
		print(x / 10);
	std::putchar(x % 10 + '0');
}

int main() {
	int n, m;
	std::cin >> n >> m;
	i128 sum = 0;
	while (n--) {
		std::vector<int> v(m);
		for (int i = 0; i < m; ++i) {
			std::cin >> v[i];
		}
		std::vector dp(m + 1, std::vector<i128>(m + 1));
		for (int i = 0; i < m; ++i)
			dp[i][i + 1] = v[i];
		for (int u = 2; u <= m; ++u) {
			for (int l = 0; l + u <= m; ++l) {
				int r = l + u;
				i128 p1 = dp[l][r - 1] * 2 + v[r - 1];
				i128 p2 = dp[l + 1][r] * 2 + v[l];
				dp[l][r] = std::max(p1, p2);
			}
		}
		sum += dp[0][m];
	}
	print(sum * 2);
	return 0;
}
