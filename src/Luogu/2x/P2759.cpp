#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

template <class Comp> // last true
ll lower(ll l, ll r, Comp check) {
	while (l < r) {
		ll m = (l + r + 1) / 2;
		if (check(m))
			l = m;
		else
			r = m - 1;
	}
	return l;
}

template <class Comp> // first true
ll upper(ll l, ll r, Comp check) {
	while (l < r) {
		ll m = (l + r) / 2;
		if (check(m))
			r = m;
		else
			l = m + 1;
	}
	return l;
}

int main() {
	ll n;
	cin >> n;
	auto f = [&](ll M) {
		double dm = M;
		return dm * log10(dm) + 1;
	};
	ll ret = upper(1, n, [&](ll M) {
		return f(M) >= n;
	});
	cout << ret;
	return 0;
}
