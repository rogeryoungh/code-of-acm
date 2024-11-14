#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

using pii = std::pair<int, int>;

auto ring(int n, int x0, int y0) {
	std::vector<pii> v;
	const int n1 = n - 1;
	v.reserve(n1 * 4);
	for (int i = 0; i < n1; ++i)
		v.emplace_back(x0, y0 + i);
	for (int i = 0; i < n1; ++i)
		v.emplace_back(x0 + i, y0 + n1);
	for (int i = 0; i < n1; ++i)
		v.emplace_back(x0 + n1, y0 + n1 - i);
	for (int i = 0; i < n1; ++i)
		v.emplace_back(x0 + n1 - i, y0);
	return v;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<std::string> v;
	for (int i = 0; i < n; ++i) {
		std::cin >> v.emplace_back();
	}
	std::vector<std::string> v2 = v;
	for (int i = 1; i <= n / 2; ++i) {
		std::vector<int> t;
		auto ringp = ring(n - (i - 1) * 2, i - 1, i - 1);
		const int o = (ringp.size() / 4) * (i % 4);
		for (int i = 0; i < ringp.size(); ++i) {
			const auto [x0, y0] = ringp[i];
			const auto [x1, y1] = ringp[(i + o) % ringp.size()];
			v2[x1][y1] = v[x0][y0];
		}
	}
	for (int i = 0; i < n; ++i) {
		std::cout << v2[i] << '\n';
	}
	return 0;
}
