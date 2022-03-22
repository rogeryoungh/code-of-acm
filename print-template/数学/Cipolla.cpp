template <typename T> T tpow(T a, ll b) {
	T ret;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a;
		a = a * a;
	}
	return ret;
}

namespace Qresidue {
ll legendre(ll a, ll p) {
	return qpow(a, (p - 1) / 2, p);
}

ll find_a(ll n, ll p) {
	for (ll a = 0; a < p; a++) {
		ll i = (a * a - n + p) % p;
		if (qpow(i, (p - 1) / 2, p) == p - 1)
			return a;
	}
	return -1;
}

ll P, I;
struct expnum {
	ll a = 1, b = 0;
};
expnum operator*(expnum i1, expnum i2) {
	return expnum{(i1.a * i2.a + i1.b * i2.b % P * I) % P, (i1.b * i2.a + i1.a * i2.b) % P};
}

std::pair<int, int> Cipolla(ll n, ll _p) {
	P = _p;
	if (n % P == 0) // 不互质的情形
		return {0, 0};
	if (legendre(n, P) != 1)
		return {-1, -1}; // 返回-1表示无解
	ll a = find_a(n, P);
	I = (a * a - n + P) % P;
	ll ans = tpow(expnum{a, 1}, (P + 1) / 2).a % P;
	if (2 * ans > P)
		ans = P - ans;
	return {ans, P - ans};
}
}; // namespace Qresidue