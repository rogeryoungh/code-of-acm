#include "basic/index.hpp"

#include "basic/qpow.cpp"

#include "math/sieve/euler.cpp"

int euler_phi(ll x) {
	ll ans = 1;
	for (int p : primes) {
		if (1ll * p * p > x)
			break;
		if (x % p == 0)
			x /= p, ans *= p - 1;
		while (x % p == 0)
			x /= p, ans *= p;
	}
	if (x > 1)
		ans *= x - 1;
	return ans;
}

int tetration_mod(int a, int b, int m) {
	if (m == 1)
		return 0;
	if (a == 0)
		return (b + 1) % 2;
	if (b == 0)
		return 1;
	if (b == 1)
		return a % m;
	if (a == 2 && b <= 4) {
		static const std::array ans = {1, 2, 4, 16, 65536};
		return ans[b] % m;
	}
	int phi = euler_phi(m);
	int d = tetration_mod(a, b - 1, phi) + phi;
	return qpow(a % m, d, m);
}
