int legendre(int a, int p) {
	return qpow(a, (p - 1) / 2, p);
}

struct FP2 {
	inline static ll P, I;
	ll a = 1, b = 0; // a+bi, i^2=a^2-n
	friend FP2 operator*(FP2 i1, FP2 i2) {
		return FP2{(i1.a * i2.a + i1.b * i2.b % P * I) % P, (i1.b * i2.a + i1.a * i2.b) % P};
	}
};

ll cipolla(ll n, ll p) {
	FP2::P = p;
	if (n % p == 0)
		return 0;
	if (legendre(n, p) != 1)
		return -1;

	ll a = -1;
	for (a = 0; a < p; a++) {
		ll i = (a * a - n + p) % p;
		if (legendre(i, p) == p - 1) {
			FP2::I = i;
			break;
		}
	}
	ll ans = tpow(FP2{a, 1}, (p + 1) / 2).a;
	return min(ans, p - ans);
}
