#include "basic/index.hpp"

#include "basic/qpow.cpp"

// @description 二次剩余(cipolla)

int legendre(int a, int p) {
	return qpow(a, (p - 1) / 2, p);
}

std::optional<int> cipolla(int n, int p) {
	if (n == 0)
		return 0;
	if (legendre(n, p) != 1)
		return std::nullopt;
	if (p == 2)
		return 1;
	for (int a = 0; a < p; a++) {
		int i = (a * a - n + p) % p;
		using FP2 = std::pair<ll, ll>;
		auto mul = [p, i](const FP2 &l, const FP2 &r) {
			auto [la, lb] = l;
			auto [ra, rb] = r;
			return FP2{(la * ra + lb * rb % p * i) % p, (lb * ra + la * rb) % p};
		};
		if (legendre(i, p) == p - 1) {
			FP2 x = {1, 1}, u = {a, 1};
			for (int b = (p + 1) / 2; b; b /= 2) {
				if (b % 2 == 1)
					x = mul(x, u);
				u = mul(u, u);
			}
			return std::min(x.first, p - x.first);
		}
	}
	return std::nullopt;
}
