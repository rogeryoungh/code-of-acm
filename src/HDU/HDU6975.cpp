#pragma region

#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>

#endif

using namespace std;
typedef long long ll;

#define _fora(i, a, n) for (ll i = (a); i <= n; i++)
#define _forz(i, a, n) for (ll i = (a); i >= n; i--)
#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')

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

void pr(ll n) {
	if (n > 9)
		pr(n / 10);
	putchar(n % 10 + '0');
}

#pragma endregion

const double PI = acos(-1.0);

const int MN = 1 << 20;

struct Comp {
	double x, y;
	Comp(double xx = 0, double yy = 0) {
		x = xx, y = yy;
	}
	Comp operator+(Comp c) {
		return Comp(x + c.x, y + c.y);
	}
	Comp operator-(Comp c) {
		return Comp(x - c.x, y - c.y);
	}
	Comp operator*(Comp c) {
		double tx = x * c.x - y * c.y;
		double ty = x * c.y + y * c.x;
		return Comp(tx, ty);
	}
};
int rev[MN];

void FFT(Comp *f, int n, int type) {
	for (int i = 0; i < n; ++i) {
		if (i < rev[i]) {
			swap(f[i], f[rev[i]]);
		}
	}
	for (int h = 2; h <= n; h <<= 1) {
		Comp step(cos(2 * PI / h), sin(2 * PI * type / h));
		for (int j = 0; j < n; j += h) {
			Comp cur(1, 0);
			for (int k = j; k < j + h / 2; k++) {
				Comp f1 = f[k], f2 = f[k + h / 2];
				f[k] = f1 + cur * f2;
				f[k + h / 2] = f1 - cur * f2;
				cur = cur * step;
			}
		}
	}
	if (type == 1)
		return;
	for (int i = 0; i < n; i++)
		f[i].x /= n, f[i].y /= n;
}

Comp SS[MN];

char a[MN], b[MN];

ll sum[MN], ans[MN];

char ch[] = "0123456789*";

int main() {

	ll ttt = rr();
	while (ttt--) {
		ll n = rr(), m = rr();
		memset(sum, 0, sizeof(ll) * (m + n + 12));
		memset(ans, 0, sizeof(ll) * (m + 12));

		int lim = 1, lim_2;
		while (lim <= m + n)
			lim <<= 1;
		lim_2 = lim >> 1;
		for (int i = 0; i < lim; ++i) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * lim_2);
		}
		scanf("%s %s", b, a);
		ll tsum = 0;
		_fora(i, 0, m - 2) {
			tsum += b[i] == '*';
			tsum += a[i] == '*';
		}
		tsum += a[m - 1] == '*';

		reverse(a, a + m + 1);
		_fora(k, 0, 10) {
			_fora(i, 0, lim - 1) SS[i] = Comp(0, 0);
			_fora(i, 0, n - 1) SS[i].x = b[i] == ch[k];
			_fora(i, 1, m) SS[i].y = a[i] == ch[k];

			FFT(SS, lim, 1);

			_fora(i, 0, lim - 1) SS[i] = SS[i] * SS[i];

			FFT(SS, lim, -1);
			//_fora (i, 0, m + n)
			//    printf("%d ", int(SS[i].y / 2 + 0.5));
			// LN;

			if (k == 10) {
				_fora(i, 0, m + n) sum[i] -= int(SS[i].y / 2 + 0.5);
			} else {
				_fora(i, 0, m + n) sum[i] += int(SS[i].y / 2 + 0.5);
			}
		}
		_fora(i, m, n) {
			tsum += (b[i - 1] == '*') - (b[i - m - 1] == '*');
			ll tans = tsum + sum[i];
			ans[m - tans]++;
		}
		tsum = 0;
		_fora(i, 0, m) {
			tsum += ans[i];
			printf("%lld\n", tsum);
		}
	}
	return 0;
}
