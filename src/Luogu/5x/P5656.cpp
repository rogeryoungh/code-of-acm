#ifdef YCYLOCAL
#include "lab.h" //#include <bits/stdc++.h>
#else
#include <bits/stdc++.h>
#endif

using namespace std;
typedef long long ll;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _in(i, min, max) (((i) - (min)) | ((max) - (i)))
#define _dbg(x) cout << "[Log] " << #x << " = " << x << endl;
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)

inline ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (_in(c, '0', '9') < 0) {
		if (c == '-')
			w *= -1;
		c = getchar();
	}
	while (_in(c, '0', '9') >= 0) {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}
ll gcd(ll a, ll b) {
	return a ? gcd(b % a, a) : b;
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		y = 0, x = 1;
		return a;
	}
	ll t = exgcd(b, a % b, y, x);
	y = y - a / b * x;
	return t;
}
int main() {
	ll lnn = rr();
	_fora(iia, 1, lnn) {
		ll a = rr();
		ll b = rr();
		ll c = rr();
		ll d = gcd(a, b);
		if (c % d != 0) {
			printf("-1\n");
			continue;
		}
		a /= d;
		b /= d;
		c /= d;
		ll x, y;
		exgcd(a, b, x, y);
		x *= c;
		y *= c;
		if (x <= 0) {
			ll t = -x / b + 1;
			x = x % b + b;
			y = y - t * a;
			if (y <= 0) {
				printf("%lld %lld\n", x, (y % a + a));
				continue;
			}
		}
		if (y <= 0) {
			ll t = -y / a + 1;
			y = y % a + a;
			x = x - t * b;
			if (x <= 0) {
				printf("%lld %lld\n", (x % b) + b, y);
				continue;
			}
		}
		ll t = x / b;
		x = x % b;
		if (x == 0) {
			x += b;
			t--;
		}
		y += t * a;
		ll minx = x, maxy = y;
		t = y / a;
		y = y % a;
		if (y == 0) {
			y += a;
			t--;
		}
		x += t * b;
		printf("%lld %lld %lld %lld %lld\n", (x - minx) / b + 1, minx, y, x, maxy);
	}
	// printf("\n");
	return 0;
}
