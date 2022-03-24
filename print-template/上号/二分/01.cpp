template <class Comp> // last true
ll lower(ll l, ll r, Comp check) {
	if (!check(l))
		return l - 1;
	while (l < r) {
		ll m = (l + r + 1) >> 1;
		if (check(m))
			l = m;
		else
			r = m - 1;
	}
	return l;
}
