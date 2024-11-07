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

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)

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

#pragma endregion

int main() {
	ll n = rr();
	ll ans = n;
	for (ll i = 2; i * i <= n; i++) {
		ll k = 0;
		while (n % i == 0)
			k++, n /= i;
		if (k > 0)
			ans += ans / i * k * (i - 1);
	}
	if (n > 1)
		ans += ans / n * 1 * (n - 1);
	printf("%lld", ans);
	return 0;
}
