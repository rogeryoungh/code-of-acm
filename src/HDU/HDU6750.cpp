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

const ll maxn = 1e6 + 20;
const ll mod = 1e9 + 7;

using i128 = __int128_t;

bool notp[maxn];
int prime[maxn / 10], cnt;
ll mu[maxn];
void sieve(int n) {
	mu[1] = 1;
	for (ll i = 2; i <= n; i++) {
		if (!notp[i]) {
			prime[++cnt] = i;
			mu[i] = -1;
		}
		ll t = n / i;
		for (ll j = 1; j <= cnt; j++) {
			ll pj = prime[j], ti = i * pj;
			if (pj > t)
				break;
			notp[ti] = true;
			if (i % pj == 0) {
				mu[ti] = 0;
				break;
			}
			mu[ti] = mu[i] * mu[pj];
		}
	}
}

ll g[maxn];

ll G(ll n) {
	if (n <= 1e6)
		if (g[n] > 0)
			return g[n];
	i128 ret = 0;
	for (ll l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		i128 t = i128(l + r) * (r - l + 1) / 2;
		ret += t * (n / l);
	}
	if (n <= 1e6)
		g[n] = ret % mod;
	return ret % mod;
}

int main() {
	ll ttt = rr();
	sieve(1e6 + 1);
	for (ll i = 1; i <= 1e6 + 1; i++) {
		mu[i] = (mu[i - 1] + mu[i] * i) % mod;
	}
	while (ttt--) {
		ll n = rr(), sn = sqrt(n * 1.0);
		i128 ans = 0;
		for (ll l = 1, r; l <= sn; l = r + 1) {
			ll t = n / l / l;
			r = sqrt(n / (n / l / l) * 1.0);
			ans += (mu[r] - mu[l - 1]) * G(n / l / l);
		}
		ans = (ans % mod + mod) % mod;

		printf("%lld\n", ll(ans));
	}
	return 0;
}
