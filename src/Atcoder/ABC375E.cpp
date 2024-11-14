#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

using pii = std::pair<int, int>;

#define dbg(x) #x << " = " << x << ", "

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
	os << "[ ";
	if (!v.empty()) {
		os << v[0];
		for (int i = 1; i < v.size(); ++i) {
			os << ", " << v[i];
		}
	}
	return os << "]";
}

int main() {
	int n;
	std::cin >> n;
	std::vector<pii> v(n);
	int sumb = 0, cnt3 = 0;
	for (auto &[a, b] : v) {
		std::cin >> a >> b;
		sumb += b;
		cnt3 += a == 3;
	}
	const int B = sumb / 3 + 1;
	std::vector dp(B, std::vector<int>(B, 1E6));
	dp[0][0] = n - cnt3;
	std::vector ndp = dp;
	// std::cout << dbg(dp) << std::endl;

	for (int u = 0; u < n; ++u) {
		// ndp = dp;
		std::swap(ndp, dp);
		auto f = [&](int dx, int dy, int t = 1) {
			for (int i = 0; i < B; ++i) {
				for (int j = 0; j < B; ++j) {
					int tx = i + dx, ty = j + dy;
					bool in = 0 <= tx && tx < B && 0 <= ty && ty < B;
					if (in) {
						dp[tx][ty] = std::min(ndp[tx][ty], ndp[i][j] + t);
					}
				}
			}
		};
		auto [a, b] = v[u];
		if (a == 3) {
			f(b, 0, 1);
			f(0, b, 1);
		} else if (a == 1) {
			f(0, b, 0);
			f(b, 0, -1);
		} else if (a == 2) {
			f(b, 0, 0);
			f(0, b, -1);
		}
		// std::cout << dbg(u) << std::endl;
	}
	// std::cout << dbg(dp) << std::endl;

	if (sumb % 3 != 0) {
		std::cout << "-1";
	} else {
		int ans = dp[sumb / 3][sumb / 3];
		std::cout << (ans > n ? -1 : ans);
	}

	return 0;
}
