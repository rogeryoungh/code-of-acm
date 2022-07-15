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

const ll mod = 1e9 + 7;
#define ACM_MOD mod
const int maxn = 1e6 + 5;

ll cc[110][110];

void pre_binom(ll n) {
	for (ll i = 0; i <= n; i++) {
		cc[i][0] = 1;
		for (ll j = 1; j <= i; j++) {
			cc[i][j] = (cc[i - 1][j - 1] + cc[i - 1][j]) % mod;
		}
	}
}

ll mo(ll n, ll m = ACM_MOD) {
	return (n + m) % m;
}

namespace min25 {

ll n, prime[maxn], cnt, w[maxn], c[maxn];
ll sqrt_n, m, kkk;

ll f_p(ll e, ll k) {
	return cc[e + k - 1][k - 1];
}

int id(ll x) {
	return x <= sqrt_n ? x : m - (n / x) + 1;
}

void pre(ll _n) {
	n = _n, sqrt_n = sqrt(n + 0.01);
	m = cnt = 0;
	for (ll l = 1, r; l <= n; l = r + 1) {
		w[++m] = r = n / (n / l);
		c[m] = r - 1;
	}
	for (ll p = 2; p <= sqrt_n; p++) {
		if (c[p] != c[p - 1]) {
			prime[++cnt] = p;
			for (ll j = m; w[j] >= p * p; j--) {
				c[j] -= c[id(w[j] / p)] - c[p - 1];
			}
		}
	}
}

ll F(ll n, int k, int tk) {
	if (n <= prime[k])
		return 0;
	ll ret = (c[id(n)] - c[prime[k]]) * tk;
	for (int i = k + 1; i <= cnt && prime[i] * prime[i] <= n; i++) {
		ll pi = prime[i], pk = pi;
		for (int e = 1; pk * pi <= n; e++, pk *= pi)
			ret = (ret + f_p(e, tk) * F(n / pk, i, tk) + f_p(e + 1, tk));
	}
	return ret % mod;
}

ll solve(ll n, ll k) {
	return F(n, 0, k);
}

} // namespace min25

int main() {
	ll x, k;
	pre_binom(70);
	while (scanf("%lld %lld", &x, &k) != EOF) {
		min25::pre(x);
		ll ans = 0;
		for (ll i = 1; i <= k; i++) {
			if (cc[k][i] == 0)
				continue;
			ll tsum = cc[k][i] * min25::solve(x, i);
			if ((k - i) % 2 == 1)
				tsum *= -1;
			ans += tsum;
		}
		printf("%lld\n", mo(ans % mod));
	}
	return 0;
}
