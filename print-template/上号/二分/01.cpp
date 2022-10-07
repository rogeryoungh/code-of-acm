template <class Comp> // last true
ll lower(ll l, ll r, Comp check) {
	if (l >= r or not check(l))
		return r;
	while (r - l > 1) {
		ll m = l + (r - l) / 2;
		(check(m) ? l : r) = m;
	}
	return l;
}
