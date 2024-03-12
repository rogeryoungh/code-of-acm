#pragma once
#include "../base.hpp"

// #region snippet
i64 bsearch_l(i64 l, i64 r, auto check) {
	while (r - l > 1) {
		i64 m = l + (r - l) / 2;
		check(m - 1) ? r = m : l = m;
	}
	return check(l) ? l : r;
}

i64 bsearch_r(i64 l, i64 r, auto check) {
	while (r - l > 1) {
		i64 m = l + (r - l) / 2;
		check(m) ? l = m : r = m;
	}
	return check(l) ? l : r;
}
// #endregion snippet
