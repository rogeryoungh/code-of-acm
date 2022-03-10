pair<ll, ll> exgcd(ll a, ll b) {
	if (!b) {
		return {1, 0};
	}
	auto [y, x] = exgcd(b, a % b);
	return {x, y - a / b * x};
}

ll inv(ll a, ll p) {
	auto [x, y] = exgcd(a, p);
	return (x % p + p) % p;
}

ll crt(const vector<ll> &aa, const vector<ll> &nn) {
	ll prod = 1, ret = 0, n = aa.size();
	for (auto ni : nn)
		prod *= ni;
	for (int i = 0; i < n; i++) {
		ll m = prod / nn[i];
		ret += aa[i] * m * inv(m, nn[i]);
		ret %= prod;
	}
	return ret;
}
