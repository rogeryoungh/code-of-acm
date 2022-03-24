ll inv(ll a, ll p) {
	auto [x, y] = exgcd(a, p);
	return (x % p + p) % p;
}