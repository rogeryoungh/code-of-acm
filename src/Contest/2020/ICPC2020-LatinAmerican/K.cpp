// GENERATE FROM https://github.com/rogeryoungh/code-of-acm

// Problem: K. Keylogger
// Contest: Codeforces - 111
// URL: https://codeforces.com/gym/349021/problem/K
// Date: 2021-10-14 16:51:33
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

const int maxk = 800, maxn = 1e4 + 5, mod = 1e9 + 7;
ll TT[maxk][maxk];
ll PP[maxn];

ll dp[maxn][maxk];

ll add(ll a, ll b) {
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

ll sub(ll a, ll b) {
	a -= b;
	if (a < 0)
		a += mod;
	return a;
}

int main() {
	ll K = rr(), L = rr();
	for (int i = 1; i <= K; i++) {
		for (int j = 1; j <= K; j++) {
			TT[i][j] = rr();
		}
	}
	ll N = rr();
	for (int i = 1; i <= N - 1; i++) {
		PP[i] = rr();
	}
	dp[0][1] = 1;
	for (int i = 1; i <= N - 1; i++) {
		ll pi = PP[i];
		ll sum_dp = 0;
		for (int j = 1; j <= K; j++) {
			ll dp_j = add(sum_dp, dp[i - 1][j]);
			sum_dp = dp_j;
			int tl = lower_bound(TT[j] + 1, TT[j] + K + 1, pi - L) - TT[j];
			int tr = upper_bound(TT[j] + 1, TT[j] + K + 1, pi + L) - TT[j];
			tr--;
			if (tl > tr)
				continue;
			dp[i][tl] = add(dp[i][tl], dp_j);
			dp[i][tr + 1] = sub(dp[i][tr + 1], dp_j);
		}
	}
	ll ans = 0, sum = 0;
	for (int i = 1; i <= K; i++) {
		sum = add(sum, dp[N - 1][i]);
		ans = add(ans, sum);
	}
	printf("%lld\n", ans);
	return 0;
}
