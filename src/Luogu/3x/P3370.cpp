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

struct Data {
	ll x, y;
	bool operator!=(Data t) {
		if (x == t.x && y == t.y)
			return false;
		return true;
	}
	bool operator<(Data t) {
		return x < t.x;
	}
} aa[10086];
char s[1686];

ll hashs(ll i, ll mod) {
	ll len = strlen(s + 1);
	ll sum = 0;
	_fora(i, 1, len) {
		sum = (sum * 131 + s[i]) % mod;
	}
	return sum;
}

int main() {
	ll ttt = rr();
	ll t = 1;
	_fora(j, 1, ttt) {
		scanf("%s", s + 1);
		aa[j].x = hashs(1, 19260817);
		aa[j].y = hashs(2, 19660813);
		// printf("%lld %lld\n",aa[j].x,aa[j].y);
	}
	sort(aa + 1, aa + 1 + ttt);
	_fora(j, 2, ttt) if (aa[j] != aa[j - 1]) t++;
	printf("%lld\n", t);
	return 0;
}
