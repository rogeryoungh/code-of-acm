#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

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

ll lsqrt(ll x) {
	return lower(1, 3E9 + 5, [&](ll M) {
		return M * M <= x;
	});
}

const ll N = 1E5;

vector<ll> v1, v2;

void pre(ll n) {
	v1.resize(n + 1), v2.resize(n + 1);
	v2[1] = v1[1] = 1;
	ll u = 2;
	for (ll i = 2; i <= n; i++) {
		if (u * u == i)
			u++;
		v1[i] = v1[i - 1] + v1[u - 1];
		v2[i] = v2[i - 1] + 2 * (i - 1) * v1[i - 1] + v1[i];
	}
}

int main() {
	int T;
	cin >> T;
	pre(N);
	while (T--) {
		ll x;
		cin >> x;
		ll n = lsqrt(x), sn = lsqrt(n), ret = v2[sn];
		cout << ret + (n - sn * sn) * v1[sn] << "\n";
	}
	return 0;
}
