template <class Comp> // first true
ll upper(ll l, ll r, Comp check) {
	if (!check(r))
		return r + 1;
	while (l < r) {
		ll m = (l + r) >> 1;
		if (check(m))
			r = m;
		else
			l = m + 1;
	}
	return l;
}
