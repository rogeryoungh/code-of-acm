#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::string s, r;
		std::cin >> n >> s >> r;
		std::array<int, 2> cnt{0};
		for (char c : s) {
			cnt[c - '0'] += 1;
		}
		bool flag = true;
		for (char c : r) {
			if (cnt[0] <= 0 || cnt[1] <= 0) {
				flag = false;
			}
			if (c == '0') {
				cnt[1] -= 1;
			} else {
				cnt[0] -= 1;
			}
			if (cnt[0] < 0 || cnt[1] < 0) {
				flag = false;
			}
		}
		std::cout << (flag ? "YES" : "NO") << "\n";
	}
	return 0;
}
