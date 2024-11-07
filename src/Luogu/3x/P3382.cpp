#ifdef YCYLOCAL
#include "lab.hpp"
#else
#include <bits/stdc++.h>
#endif
using namespace std;
typedef long long ll;
typedef long double ld;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _in(i, min, max) (((i) - (min)) | ((max) - (i)))
#define _dbg(x) cout << "[Log] " << #x << " = " << x << endl;
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)

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

const ld eps = 1e-6;

ld aa[1000];
ll n;

ld f(ld x) {
	ld sum = 0;
	ld xn = 1.0;
	_forz(i, n + 1, 1) {
		sum += xn * aa[i];
		xn *= x;
	}
	return sum;
}

int main() {
	n = rr();
	ld l, r;
	scanf("%Lf%Lf", &l, &r);
	_fora(i, 1, n + 1) {
		scanf("%Lf", &aa[i]);
	}
	while (r - l > eps) {
		ld mid = (r + l) / 2;
		if (f(mid + eps) > f(mid - eps))
			l = mid;
		else
			r = mid;
	}
	printf("%Lf\n", l);
	return 0;
}