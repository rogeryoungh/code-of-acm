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

const ll mod = 1e9 + 9, phi_mod = mod - 1;
const ll maxn = 1e5 + 10;
#define ACM_MOD mod

/*
#include "template/basic/qpow.hpp"
#include "template/basic/inv.hpp"
#include "template/basic/mo.hpp"
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

#ifndef ACM_BASIC_INV_H
#define ACM_BASIC_INV_H

#ifdef ACM_MOD
ll inv(ll a, ll m = ACM_MOD) {
#else
ll inv(ll a, ll m) {
#endif
	return qpow(a, m - 2, m);
}

#endif
#ifndef ACM_BASIC_MO_H
#define ACM_BASIC_MO_H

#ifdef ACM_MOD
ll mo(ll n, ll m = ACM_MOD) {
#else
ll mo(ll n, ll m) {
#endif
	return (n + m) % m;
}

#ifdef ACM_MOD
ll momo(ll n, ll m = ACM_MOD) {
#else
ll momo(ll n, ll m) {
#endif
	return ((n % m) + m) % m;
}

#endif

#pragma endregion
// TEMPLATE END

const ll sqrt_5 = 383008016;
const ll A = mo((1 + sqrt_5) * inv(2)), B = momo((1 - sqrt_5) * inv(2));

ll euler_pow(ll a, ll b) {
	return qpow(a, b % phi_mod);
}

ll fac[maxn], ind[maxn];
void pre(ll n) {
	fac[0] = 1;
	for (ll i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i % mod;
	}
	ind[n] = inv(fac[n]);
	for (ll i = n - 1; i >= 0; i--) {
		ind[i] = ind[i + 1] * (i + 1) % mod;
	}
}

ll binom(ll a, ll b) {
	if (b > a)
		b = a - b;
	return fac[a] * ind[b] % mod * ind[a - b] % mod;
}

int main() {
	pre(1e5 + 1);
	ll ttt = rr();
	while (ttt--) {
		ll n = rr(), c = rr(), k = rr();
		ll step1 = euler_pow(A * inv(B) % mod, c), step2 = euler_pow(step1, n + 1);
		ll T1 = euler_pow(B, c % phi_mod * k), T2 = euler_pow(T1, n + 1);
		ll ans = 0;
		for (ll j = 0; j <= k; j++) {
			ll tsum = binom(k, j);
			if (T1 != 1) {
				tsum = tsum * (T2 - 1) % mod * inv(T1 - 1) % mod;
			} else {
				tsum = (n + 1) % mod * tsum % mod;
			}
			if ((k - j) % 2 == 1)
				tsum *= -1;
			ans = mo(ans + tsum);
			T1 = T1 * step1 % mod, T2 = T2 * step2 % mod;
		}
		ans = ans % mod * euler_pow(inv(A - B), k) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
