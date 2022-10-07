template <class PAIR>
ll crt(const vector<PAIR> &am) {
	ll prod = 1, ret = 0;
	for (auto [a, m] : am)
		prod *= m;
	for (auto [a, m] : am) {
		ll u = prod / m, v = inv_gcd(u, m);
		ret = (ret + a * u * v) % prod;
	}
	return ret;
}
