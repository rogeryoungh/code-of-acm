// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-11 10:35:08.297698

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128_t;
using ull = unsigned long long;
using ld = long double;

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
		ll n = rr(), k = rr(), Max = 0;
		unordered_map<int, int> mp;
		for (int i = 0; i < n; i++) {
			ll ai = rr();
			if (k > 0)
				mp[ai] = 1;
			Max = max(Max, ai);
		}
		if (k == 0) {
			printf("%lld\n", n);
			continue;
		}
		ll e = 0;
		for (int i = 0; i < 1e5 + 10; i++) {
			if (mp.count(i) == 0) {
				e = i;
				break;
			}
		}
		ll sz = mp.size(), Mex = (e + Max + 1) / 2;
		if (Mex > Max) {
			printf("%lld\n", sz + k);
		} else {
			sz += 1 - mp.count(Mex);
			printf("%lld\n", sz);
		}
	}
	return 0;
}