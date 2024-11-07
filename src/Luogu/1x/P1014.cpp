#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <bits/stdc++.h>
#endif

using namespace std;
typedef long long ll;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _in(i, min, max) (((i) - (min)) | ((max) - (i)))
#define _dbg(...) printf(__VA_ARGS__)

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

void solve() {
	ll n = rr();
	ll k = (ll)(sqrt(8.0 * n - 7) + 1) / 4;
	ll t = n - k * (2 * k - 1) - 1;
	printf("%lld/", min(t, 4 * k - t) + 1);

	k = (ll)(sqrt(8.0 * n - 7) - 1) / 4;
	t = n - k * (2 * k + 1) - 1;
	printf("%lld\n", min(t, 4 * k + 2 - t) + 1);
}

int main() {
#ifdef RYLOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	solve();

#ifdef RYLOCAL
	printf("Time cost : %lf ms\n", clock() * 1000.0 / CLOCKS_PER_SEC);
#endif
	return 0;
}
