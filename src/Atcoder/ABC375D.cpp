#include <bits/stdc++.h>

using i64 = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

#define dbg(x) #x << " = " << x << ", "

int main() {
	std::string s;
	std::cin >> s;
	int n = s.length();
	using arr26 = std::array<int, 26>;
	std::vector<arr26> pre(n), suf(n);
	for (int i = 0; i < n; ++i) {
		if (i > 0)
			pre[i] = pre[i - 1];
		pre[i][s[i] - 'A'] += 1;
	}
	for (int i = n - 1; i >= 0; --i) {
		if (i + 1 < n)
			suf[i] = suf[i + 1];
		suf[i][s[i] - 'A'] += 1;
	}
	i64 ans = 0;
	for (int i = 1; i < n - 1; ++i) {
		i64 tsum = 0;
		for (int j = 0; j < 26; ++j) {
			tsum += 1ll * pre[i - 1][j] * suf[i + 1][j];
		}
		ans += tsum;
	}
	std::cout << ans;
	return 0;
}
