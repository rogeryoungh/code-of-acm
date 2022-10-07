ll inv_gcd(ll a, ll p) {
	return (std::get<0>(exgcd(a, p)) % p + p) % p;
}
