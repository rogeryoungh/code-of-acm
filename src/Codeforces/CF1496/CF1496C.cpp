// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-11 17:06:54.690510

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128_t;
using ull = unsigned long long;
using ld = long double;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')
#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (!isdigit(c))
		w = 1 - 2 * (c == '-'), c = getchar();
	while (isdigit(c))
		s = s * 10 + c - '0', c = getchar();
	return s * w;
}

// END OF HEADER

const int maxn = 1e5 + 10;

double mx[maxn], py[maxn];

int main() {
	ll T = rr();
	while (T--) {
		ll n = rr();
		ll cx = 0, cy = 0;
		int cnt_m = 0, cnt_y = 0;
		for (int i = 0; i < n * 2; i++) {
			ll x = rr(), y = rr();
			if (x == 0) {
				py[cy++] = abs(y);
			} else {
				mx[cx++] = abs(x);
			}
		}
		sort(mx, mx + n);
		sort(py, py + n);
		double ans = 0;
		for (int i = 0; i < n; i++) {
			ans += sqrt(py[i] * py[i] + mx[i] * mx[i]);
		}
		printf("%.15lf\n", ans);
	}
	return 0;
}