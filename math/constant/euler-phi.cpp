#include "basic/index.hpp"

#include "math/sieve/euler.cpp"

ll euler_phi(ll x) {
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
