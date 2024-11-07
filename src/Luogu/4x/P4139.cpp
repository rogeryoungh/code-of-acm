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

const ll MN = 1e7 + 100;

ll euler_phi(ll n) {
	ll ans = n;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans = ans / i * (i - 1);
			while (n % i == 0)
				n /= i;
		}
	}
	if (n > 1)
		ans = ans / n * (n - 1);
	return ans;
}

ll qpow(ll a, ll b, ll p) {
	ll rst = p != 1;
	for (; b > 0; b >>= 1) {
		if (b & 1)
			rst = a * rst % p;
		a = a * a % p;
	}
	return rst;
}

ll solve(ll p) {
	ll phi_p = euler_phi(p);
	if (p <= 2)
		return 0;
	return qpow(2, solve(phi_p) + phi_p, p);
}

int main() {
	ll ttt = rr();
	while (ttt--) {
		ll p = rr();
		printf("%lld\n", solve(p));
	}
	return 0;
}
