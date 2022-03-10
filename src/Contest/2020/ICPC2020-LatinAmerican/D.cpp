// GENERATE FROM https://github.com/rogeryoungh/code-of-acm

// Problem: D. Dividing Candy
// Contest: Codeforces - 111
// URL: https://codeforces.com/gym/349021/problem/D
// Date: 2021-10-14 13:15:50
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

const int maxn = 2e5 + 86;

ll aa[maxn];

int main() {
	ll n = rr();
	if (n == 1) {
		printf("N\n");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		int t = rr();
		aa[t]++;
	}
	int tot = 0;
	for (int i = 0; i < maxn; i++) {
		aa[i + 1] += aa[i] / 2;
		aa[i] %= 2;
		if (aa[i] > 0)
			tot++;
	}
	// printf("%d", tot);
	if (tot <= 2)
		printf("Y\n");
	else
		printf("N\n");
	return 0;
}