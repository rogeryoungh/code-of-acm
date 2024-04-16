#include <bits/stdc++.h>
using ll = long long;

using namespace std;

#define _fora(i, a, n) for (int i = (a); i <= (n); i++)
#define _forz(i, a, n) for (int i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _ifin(i, min, max) ((((i) - (min)) | ((max) - (i))) >= 0)
#define _ifout(i, min, max) ((((i) - (min)) | ((max) - (i))) < 0)
#define ri register int

inline int rr() {
	int s = 0, w = 1;
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

int dmax[205][205];
int dmin[205][205];
int n;
int f[205];
int s[205];

int main() {
	n = rr();
	_fora(i, 1, n * 2) {
		if (i <= n)
			f[i + n] = f[i] = rr();
		s[i] = s[i - 1] + f[i];
	}
	// int p = 0;
	_fora(len, 2, n) {
		_fora(i, 1, 2 * n - len + 1) {
			int j = i + len - 1;
			int mmax = 0;
			int mmin = 0x3f3f3f3f;
			_fora(k, i, j - 1) {
				mmax = max(mmax, dmax[i][k] + dmax[k + 1][j] + s[j] - s[i - 1]);
				mmin = min(mmin, dmin[i][k] + dmin[k + 1][j] + s[j] - s[i - 1]);
				// printf(" %d %d %d %d\n",i,j,k,mmin);
			}
			dmax[i][j] = mmax;
			dmin[i][j] = mmin;
			// printf("%d %d %d %d\n",i,j, i,mmin);
		}
	}
	int rst = 0x3f3f3f3f;
	_fora(p, 0, n - 1) {
		rst = min(rst, dmin[p + 1][p + n]);
	}
	printf("%d\n", rst);
	rst = 0;
	_fora(p, 0, n - 1) {
		rst = max(rst, dmax[p + 1][p + n]);
	}

	printf("%d", rst);

	printf("\n");
	return 0;
}
