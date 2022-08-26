#include "basic/index.hpp"

// @description 二分

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