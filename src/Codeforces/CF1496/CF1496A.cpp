// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-10 22:09:26.809968

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

char s[100086];

int main() {
	ll T = rr();
	while (T--) {
		ll n = rr(), k = rr();
		scanf("%s", s + 1);
		bool flag = true;
		ll l = 1, r = n;
		while (l < r) {
			if (s[l] != s[r]) {
				flag = false;
				break;
			}
			l++, r--;
		}
		if (l > r)
			l--, r--;
		if (l > k) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}