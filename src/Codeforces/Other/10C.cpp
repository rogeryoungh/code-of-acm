#include <bits/stdc++.h>

template <class T>
using V = std::vector<T>;
using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

int main() {
	int n;
	std::cin >> n;
	V<int> a(9);
	for (int i = 0; i < 9; i++) {
		a[i] = n / 9 + (i <= n % 9);
	}
	a[0]--;

	ll ans = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			ans += 1ll * a[i] * a[j] * a[i * j % 9];
		}
	}
	for (int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans -= 1ll * (r - l + 1) * (n / l);
	}
	std::cout << ans;

	return 0;
}
