#pragma region

#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <bits/stdc++.h>
#endif
using namespace std;
typedef long long ll;
typedef long double ld;

#define _lb(x) ((x) & (-x))
#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _in(i, min, max) (((i) - (min)) | ((max) - (i)))
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)
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
	while (c >= '0' && c <= '9')
		s = s * 10 + c - '0', c = getchar();
	return s * w;
}

#pragma endregion

const ll MN = 2e5 + 10;

ll vv[MN], ww[MN], li[MN], ri[MN];

ll n, m, s;

ll f1[MN], f2[MN];

ll sum(ll w) {
	_fora(i, 1, n) {
		ll f = ww[i] >= w;
		f1[i] = f1[i - 1] + f;
		f2[i] = f2[i - 1] + f * vv[i];
	}
	ll sum = 0;
	_fora(k, 1, m) {
		ll l = li[k], r = ri[k];
		sum += (f1[r] - f1[l - 1]) * (f2[r] - f2[l - 1]);
	}
	// printf("sum %lld %lld\n", w, sum);
	return sum;
}

int main() {
	n = rr();
	m = rr();
	s = rr();

	ll minw = 0x3f3f3f3f;
	ll maxw = 0;
	f1[0] = f2[0] = 0;

	_fora(i, 1, n) {
		ww[i] = rr();
		vv[i] = rr();
		maxw = max(ww[i], maxw);
		minw = min(ww[i], minw);
	}

	_fora(i, 1, m) {
		li[i] = rr();
		ri[i] = rr();
	}

	ll l = minw;
	ll r = maxw + 1;

	while (l < r) {
		// printf("%lld\n", l);
		int mid = (l + r) >> 1;
		if (sum(mid) <= s)
			r = mid;
		else
			l = mid + 1;
	}
	ll rst = min(sum(l - 1) - s, s - sum(l));
	printf("%lld", rst);
	return 0;
}
