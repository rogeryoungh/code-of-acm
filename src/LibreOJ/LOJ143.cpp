// Author: Roger Young | Date:

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER

using i128 = __int128_t;

ll qpow128(ll a, ll b, ll m) {
	ll ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = (i128)ret * a % m;
		a = (i128)a * a % m;
	}
	return ret;
}

bool miller_rabbin(ll n) {
	if (n <= 3)
		return n >= 2;
	ll a = n - 1, b = 0;
	while (1 - (a & 1))
		a >>= 1, ++b;
	ll prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for (auto x : prime) {
		if (n == x)
			return true;
		ll v = qpow128(x, a, n);
		if (v == 1 || v == n - 1)
			continue;
		ll j;
		for (j = 0; j < b; j++) {
			v = (i128)v * v % n;
			if (v == n - 1)
				break;
		}
		if (j >= b)
			return false;
	}
	return true;
}

int main() {
	ll x;
	while (cin >> x) {
		if (miller_rabbin(x)) {
			cout << "Y\n";
		} else {
			cout << "N\n";
		}
	}
	return 0;
}