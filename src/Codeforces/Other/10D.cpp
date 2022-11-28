#include <bits/stdc++.h>

template <class T>
using V = std::vector<T>;
using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

#define dbg(x) #x << " = " << x << ", "

// @description 二维数组

template <class T>
struct VV {
	int x, y;
	V<T> m;
	VV(int a, int b, const T &v = T()) : x(a), y(b), m(a * b, v) {}
	auto operator[](int i) {
		return m.begin() + i * y;
	}
	auto operator[](int i) const {
		return m.begin() + i * y;
	}
};

int main() {
	int n;
	std::cin >> n;
	V<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	int m;
	std::cin >> m;
	V<int> b(m + 1);
	for (int j = 1; j <= m; j++) {
		std::cin >> b[j];
	}
	V<int> dp(m + 1), pre(m + 1, -1);
	for (int i = 1; i <= n; i++) {
		int p = 0;
		for (int j = 1; j <= m; j++) {
			if (a[i] == b[j]) {
				dp[j] = dp[p] + 1, pre[j] = p;
			} else if (a[i] > b[j] && dp[p] < dp[j]) {
				p = j;
			}
		}
	}
	int p = std::max_element(dp.begin(), dp.end()) - dp.begin();
	V<int> ans;
	while (p > 0) {
		ans.push_back(b[p]);
		p = pre[p];
	}
	std::reverse(ans.begin(), ans.end());
	std::cout << ans.size() << '\n';
	for (auto i : ans) {
		std::cout << i << ' ';
	}
	return 0;
}
