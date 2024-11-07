#pragma region

#ifdef RYLOCAL
#include "lab.hpp"
#else
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

#endif
using namespace std;
typedef long long ll;
typedef long double ld;

#define _lb(x) ((x) & (-x))
#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _in(i, min, max) (((i) - (min)) | ((max) - (i)))
#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define _dbg(...) printf(__VA_ARGS__)
#define LN putchar('\n');

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			w = -1;
		c = getchar();
	}
	while ('0' <= c && c <= '9') {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

void pr(int x) {
	if (x >= 10)
		pr(x / 10);
	putchar(x % 10 + '0');
}

#pragma endregion

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
	ll a = rr(), b = rr();
	printf("%lld", inv(a, b));
	return 0;
}
