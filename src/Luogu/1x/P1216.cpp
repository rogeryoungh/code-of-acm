#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

inline ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		s = s * 10 + c - '0', c = getchar();
	return s * w;
}

ll aa[1086];
ll bb[1086];

int main() {
	ll r = rr();
	memset(aa, 0, sizeof(aa));
	for (ll i = 1; i <= r; i++) {
		for (ll j = 1; j <= (i); j++) {
			bb[j] = rr();
		}
		for (ll j = i; j >= 1; j--) {
			aa[j] = max(aa[j], aa[j - 1]) + bb[j];
		}
	}
	ll mmax = 0;
	for (ll i = 1; i <= r; i++) {
		mmax = max(mmax, aa[i]);
	}
	printf("%lld\n", mmax);
	return 0;
}
