tuple<ll, ll, ll> exgcd(ll a, ll b) {
	if (b == 0) {
		return {1, 0, a};
	} else {
		auto [y, x, g] = exgcd(b, a % b);
		return {x, y - a / b * x, g};
	}
}
