#include "basic/index.hpp"

#include "math/exgcd.cpp"

// @description 扩展中国剩余定理

#include "using/i128.cpp"

template<class PAIR>
ll excrt(const std::vector<PAIR> &am) {
	auto [ans, M] = am[0];
	for (auto [a, m] : am) {
		if (M % m == 0 && ans % m == a)
			continue;
		ll B = (a - ans % m + m) % m;
		auto [x, y, g] = exgcd(M, m);
		if (B % g != 0)
			return -1;
		x = i128(x) * (B / g) % (m / g);
		ans += M * x, M *= m /g;
		ans = (ans + M) % M;
	}
	return ans;
}
