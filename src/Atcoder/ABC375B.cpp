#include <iostream>
#include <cmath>

using i64 = long long;
using f64 = double;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

f64 dis(i64 x, i64 y) {
	return std::sqrtl(x * x + y * y);
}

int main() {
	int n;
	i64 px = 0, py = 0;
	std::cin >> n;
	f64 ans = 0;
	for (int i = 0; i < n; ++i) {
		i64 x, y;
		std::cin >> x >> y;
		ans += dis(x - px, y - py);
		px = x, py = y;
	}
	ans += dis(px, py);
	std::printf("%.20lf", ans);

	return 0;
}
