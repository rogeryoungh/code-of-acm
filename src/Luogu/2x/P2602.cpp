#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <bits/stdc++.h>
#endif
using namespace std;
typedef long long ll;
typedef long double ld;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _in(i, min, max) (((i) - (min)) | ((max) - (i)))
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)
#define _dbg(...) printf(__VA_ARGS__)

int ry_solve();

inline ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		s = s * 10 + c - '0', c = getchar();
	return s * w;
}

void pr(int n, int x) {
	char c = n % x;
	c += x > 10 ? 'A' - 10 : '0';
	if (n >= x)
		pr(n / x, x);
	putchar(c);
}

int main() {
#ifdef RYLOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ry_solve();

#ifdef RYLOCAL
	printf("Time cost : %lf ms\n", clock() * 1000.0 / CLOCKS_PER_SEC);
#endif
	return 0;
}

#define main ry_solve
// Head File End

ll addup(ll n, ll x) {
	ll m = 1, j = 1;
	ll ans = 0;
	while (m <= n) {
		ll a = n / (m * 10), b = n / m % 10, c = n % m;
		ans += a * m;
		if (x > 0) {
			if (b > x)
				ans += m;
			if (b == x)
				ans += c + 1;
		} else {
			if (b == x)
				ans += c + 1 - m;
		}
		m *= 10;
	}
	return ans;
}

int main() {
	ll i = rr();
	ll j = rr();
	for (ll k = 0; k < 10; k++) {
		ll ans = addup(j, k) - addup(i - 1, k);
		printf("%lld ", ans);
	}
	return 0;
}
