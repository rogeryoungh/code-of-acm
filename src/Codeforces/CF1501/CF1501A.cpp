// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-24 13:10:03.458648

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')
#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (!isdigit(c))
		w = 1 - 2 * (c == '-'), c = getchar();
	while (isdigit(c))
		s = s * 10 + c - '0', c = getchar();
	return s * w;
}

// END OF HEADER

int main() {
	ll T = rr();
	while (T--) {
		ll n = rr();
		vector<int> a(n), b(n), tm(n);
		for (int i = 1; i <= n; i++) {
			a[i] = rr(), b[i] = rr();
		}
		for (int i = 1; i <= n; i++) {
			tm[i] = rr();
		}
		ll time = 0;
		for (int i = 0; i < n; i++) {
			ll t1 = (b[i] - a[i] + 1) / 2;
			ll t2 = b[i] - time;
			time += max({t1, t2, 0ll});
			time += a[i + 1] - b[i] + tm[i + 1];
		}
		printf("%lld\n", time);
	}
	return 0;
}
