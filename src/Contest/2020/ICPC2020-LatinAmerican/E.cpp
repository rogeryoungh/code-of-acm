// GENERATE FROM https://github.com/rogeryoungh/code-of-acm

// Problem: E. Excellent Views
// Contest: Codeforces - 111
// URL: https://codeforces.com/gym/349021/problem/E
// Date: 2021-10-14 13:53:16
//
// Powered by CP Editor (https://cpeditor.org)

#define RYLOCAL

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

// END OF HEADER

const int maxn = 1e5 + 86;

ll aa[maxn];
ll li[maxn], ri[maxn];
ll ss[maxn];
ll ans[maxn];

int main() {
	ll n = rr();
	for (int i = 1; i <= n; i++) {
		aa[i] = rr();
	}
	aa[0] = aa[n + 1] = 0x3f3f3f3f;

	int p = 0;
	ll *s = ss + 1;
	for (int i = 1; i <= n + 1; i++) {
		if (aa[i] < aa[s[p]]) {
			s[++p] = i;
		} else {
			while (aa[s[p]] < aa[i]) {
				// printf("pop %lld at %d\n", s[p], i);
				ri[s[p]] = i - 1;
				p--;
			}
			s[++p] = i;
		}
	}

	p = 0;
	for (int i = n; i >= 0; i--) {
		if (aa[i] < aa[s[p]]) {
			s[++p] = i;
		} else {
			while (aa[s[p]] < aa[i]) {
				// printf("pop %lld at %d\n", s[p], i);
				li[s[p]] = i + 1;
				p--;
			}
			s[++p] = i;
		}
	}

	for (int i = 1; i <= n; i++) {
		// printf("aa[%d] = %lld | (%lld, %lld)\n", i, aa[i], li[i], ri[i]);
		int tl = (li[i] + i + 1) / 2, tr = (ri[i] + i) / 2;
		if (li[i] == 1)
			tl = 1;
		if (ri[i] == n)
			tr = n;
		// for (int j = tl; j <= tr; j++) {
		// ans[j]++;
		// }
		ans[tl]++;
		ans[tr + 1]--;
	}

	for (int i = 1; i <= n; i++) {
		ans[i] += ans[i - 1];
		printf("%lld ", ans[i] - 1);
	}

	return 0;
}