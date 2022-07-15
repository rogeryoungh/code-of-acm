#pragma region

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
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

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

void pr(ll n) {
	if (n > 9)
		pr(n / 10);
	putchar(n % 10 + '0');
}

#pragma endregion
// END OF HEAD

const ll maxn = 2e5 + 86;
const ll mod = 1e9 + 7;
#define ACM_MOD mod

/*
#include "template/basic/qpow.hpp"
*/

// TEMPLATE BEGIN
// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
#pragma region
#ifndef ACM_BASIC_QPOW_H
#define ACM_BASIC_QPOW_H

#ifdef ACM_MOD
ll qpow(ll a, ll b, ll m = ACM_MOD) {
#else
ll qpow(ll a, ll b, ll m) {
#endif
	ll ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = a * ret % m;
		a = a * a % m;
	}
	return ret;
}

#endif

#pragma endregion
// TEMPLATE END

bool notp[maxn + 10];
int prime[maxn / 10 + 10], cnt;
ll hh[maxn + 10];
void sieve(int n) {
	hh[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!notp[i]) {
			prime[++cnt] = i;
			hh[i] = i - 1;
		}
		int t = n / i;
		for (int j = 1; j <= cnt; j++) {
			int pj = prime[j], ti = i * pj;
			if (pj > t)
				break;
			notp[ti] = true;
			if (i % pj == 0) {
				int tj = i / pj;
				if (tj % pj != 0) {
					hh[ti] = hh[tj] * (mod - pj) % mod;
				} else {
					hh[ti] = 0;
				}
				break;
			}
			hh[ti] = hh[i] * hh[pj] % mod;
		}
	}
}

ll gg[maxn + 10];

void pre(ll k, ll x) {
	sieve(maxn);
	for (ll i = 1; i <= maxn; i++) {
		gg[i] = (gg[i - 1] + qpow(i, k)) % mod;
		hh[i] = (hh[i - 1] + qpow(i, k * x % (mod - 1)) * hh[i]) % mod;
		gg[i - 1] = qpow(gg[i - 1], x);
	}
}

int main() {
	ll ttt = rr(), k = rr(), x = rr();
	pre(k, x);
	while (ttt--) {
		ll n = rr();
		ll ans = 0;
		for (ll l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ll tsum = hh[r] - hh[l - 1] + mod;
			tsum = tsum * gg[n / l] % mod;
			ans = (ans + tsum) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
