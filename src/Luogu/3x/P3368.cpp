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

int ry_solve();

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

const ll MN = 1000086;

ll aa[MN], bb[MN], cc[MN], dd[MN];

ll n, m;

void build() {
	_fora(i, 1, n) {
		cc[i] += aa[i];
		ll j = i + (i & (-i));
		if (j <= n)
			cc[j] += cc[i];
	}
}

ll ask(ll *cc, ll x) {
	ll sum = 0;
	while (x >= 1) {
		sum += cc[x];
		x -= x & (-x);
	}
	return sum;
}

void add(ll *cc, ll x, ll k) {
	while (x <= n) {
		cc[x] += k;
		x += x & (-x);
	}
}

void add(ll l, ll r, ll k) {
	add(bb, l, k);
	add(bb, r + 1, -k);
}

int main() {
	n = rr();
	m = rr();
	memset(aa, 0, sizeof(aa));
	memset(cc, 0, sizeof(cc));
	_fora(i, 1, n) {
		aa[i] = rr();
	}
	build();
	_fora(i, 1, m) {
		ll op = rr();
		if (op == 1) {
			ll x = rr();
			ll y = rr();
			ll k = rr();
			add(x, y, k);
		} else {
			ll x = rr();
			printf("%lld\n", ask(bb, x) + aa[x]);
		}
	}
	return 0;
}
