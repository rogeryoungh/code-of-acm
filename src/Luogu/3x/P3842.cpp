#include <bits/stdc++.h>
using ll = long long;

using namespace std;
#define _fora(i, a, n) for (int i = (a); i <= (n); i++)
#define _forz(i, a, n) for (int i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))

inline int rr() {
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}

int main() {
	int n = rr();
	int pl, pr;
	pl = pr = 1;
	ll dpl, dpr;
	dpl = dpr = 0;
	_fora(ia, 1, n) {
		int l, r;
		l = rr();
		r = rr();
		ll tl = min(dpl + abs(pl - r), dpr + abs(pr - r)) + r - l;
		ll tr = min(dpl + abs(pl - l), dpr + abs(pr - l)) + r - l;
		dpl = tl;
		dpr = tr;
		pl = l;
		pr = r;
		// printf("%d %d %d\n",ia,dpl,dpr);
	}
	printf("%lld", min(dpl + n - pl, dpr + n - pr) + n - 1);

	printf("\n");
	return 0;
}
