ll qpow(ll a, ll b = P - 2, ll p = P) {
	ll ret = p != 1;
	for (; b > 0; b >>= 1) {
		if (b & 1)
			ret = a * ret % p;
		a = a * a % p
	}
	return ret;
}