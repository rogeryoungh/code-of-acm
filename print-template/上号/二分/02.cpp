template <class Comp> // first true
ll upper(ll l, ll r, Comp check) {
	if (l >= r or not check(r - 1))
		return r;
	while (r - l > 1) {
		ll m = l + (r - l) / 2;
		(check(m - 1) ? r : l) = m;
	}
	return l;
}
