bool miller_rabbin(ll n) {
	if (n <= 3)
		return n >= 2;
	ll a = n - 1, b = 0;
	while (1 - (a & 1))
		a >>= 1, ++b;
	for (auto p : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
		if (n == p)
			return true;
		ll v = qpow128(p, a, n);
		if (v == 1 || v == n - 1)
			continue;
		for (int j = 0; j < b && v != 1; j++) {
			ll w = (i128)v * v % n;
			if (v != n - 1 && w == 1)
				return false;
			v = w;
		}
		if (v != 1)
			return false;
	}
	return true;
}
