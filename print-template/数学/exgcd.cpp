pair<ll, ll> exgcd(ll a, ll b) {
	if (!b)
		return {1, 0};
	auto [y, x] = exgcd(b, a % b);
	return {x, y - a / b * x};
}
