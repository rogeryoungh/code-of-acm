// GENERATE FROM https://github.com/rogeryoungh/code-of-acm

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
#define _dbg(...) fprintf(stderr, __VA_ARGS__)

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

const ll maxn = 1000086;
ll num[maxn], base[maxn];

void exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		y = 0;
		x = 1;
		return; // gcd = a;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

ll inv(ll a, ll p) {
	ll x, y;
	exgcd(a, p, x, y);
	return (x % p + p) % p;
}

int main() {
	ll B = rr(), L = rr(), mod = B + 1, sum = 0;
	base[0] = 1;
	for (int i = 1; i < L; i++) {
		base[i] = base[i - 1] * B % mod;
	}
	for (int i = L - 1; i >= 0; i--) {
		ll temp = rr();
		num[i] = temp;
		sum = (sum + temp * base[i]) % mod;
	}
	if (sum == 0) {
		printf("0 0\n");
		return 0;
	}
	for (int i = L - 1; i >= 0; i--) {
		ll tsum = ((sum - num[i] * base[i]) % mod + mod) % mod;
		ll t = (mod - tsum) * inv(base[i], mod) % mod;
		if (t < num[i]) {
			printf("%lld %lld\n", L - i, t);
			return 0;
		}
	}
	printf("-1 -1\n");
	return 0;
}