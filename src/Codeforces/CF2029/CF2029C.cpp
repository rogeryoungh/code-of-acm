#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

int f(int p, int a) {
	if (p < a)
		return p + 1;
	if (p > a)
		return p - 1;
	return p;
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::vector<int> a(n + 1);
		for (int i = 1; i <= n; ++i) {
			std::cin >> a[i];
		}
		std::vector<std::array<int, 3>> dp(n + 1);
		dp[0][2] = dp[0][1] = -1;
		for (int i = 1; i <= n; ++i) {
			auto &now = dp[i], &p = dp[i - 1];
			now[0] = f(p[0], a[i]);
			now[1] = std::max(p[0], p[1]);
			now[2] = std::max(f(p[2], a[i]), f(p[1], a[i]));
			// std::cout << "DBG " << now[0] << ' ' << now[1] << ' ' << now[2] << '\n';
		}
		std::cout << std::max(dp[n][1], dp[n][2]) << '\n';
	}
	return 0;
}
