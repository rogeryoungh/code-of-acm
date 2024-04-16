#include <bits/stdc++.h>
using ll = long long;

#define _fora(i, a, n) for (int i = (a); i <= (n); i++)
#define _forz(i, a, n) for (int i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _ifin(i, min, max) if (((i - min) | (max - i)) >= 0)
#define _ifout(i, min, max) if (((i - min) | (max - i)) < 0)
#define ri register int

using namespace std;
typedef long long ll;

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

ll power(ll a, ll b, ll p) {
	ll rst = 1 % p;
	for (; b > 0; b >>= 1, a = a * a % p)
		if (b & 1)
			rst = a * rst % p;
	return rst;
}

int main() {
	ll a = rr();
	ll b = rr();
	ll c = rr();
	printf("%lld^%lld mod %lld=%lld\n", a, b, c, power(a, b, c));
	// printf("\n");
	return 0;
}
