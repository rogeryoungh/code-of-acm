#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		ll l, r, k;
		std::cin >> l >> r >> k;
		ll ans = std::max<ll>(r / k - l + 1, 0);
		std::cout << ans << '\n';
	}
	return 0;
}
