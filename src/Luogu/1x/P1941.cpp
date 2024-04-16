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

struct Shuiguan {
	int l, h;
};

int dp[10010][1010];

const int _inf = 0x3f3f3f3f;

int main() {
	int n = rr();
	int m = rr();
	int k = rr();
	int xx[10010], yy[10010];
	memset(xx, 0, sizeof(xx));
	memset(yy, 0, sizeof(yy));
	Shuiguan sg[10010];
	memset(sg, 0, sizeof(sg));
	_fora(ia, 1, n) {
		xx[ia - 1] = rr();
		yy[ia - 1] = rr();
		sg[ia].l = 0;
		sg[ia].h = m + 1;
	}
	_fora(ib, 1, k) {
		int p = rr();
		sg[p].l = rr();
		sg[p].h = rr();
	}
	memset(dp, 0x3f, sizeof(dp));

	_fora(j, 1, m) {
		dp[0][j] = 0;
	}
	dp[0][0] = _inf;
	_fora(i, 1, n) {
		_fora(j, 1, m) {
			if (j >= xx[i - 1]) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j - xx[i - 1]] + 1);
				dp[i][j] = min(dp[i][j], dp[i][j - xx[i - 1]] + 1);
			}
			if (j == m) {
				_fora(ja, j - xx[i - 1], m) {
					dp[i][j] = min(dp[i][j], dp[i - 1][ja] + 1);
					dp[i][j] = min(dp[i][j], dp[i][ja] + 1);
				}
			}
			// if(dp[i][j]<_inf) {
			//     printf("%d %d %d\n",i,j,dp[i][j]);
			// }
		}
		_fora(j, sg[i].l + 1, sg[i].h - 1) {
			if (j + yy[i - 1] <= m) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j + yy[i - 1]]);
			}
		}
		_fora(j, 1, sg[i].l) {
			dp[i][j] = _inf;
		}
		_fora(j, sg[i].h, m) {
			dp[i][j] = _inf;
		}
	}
	int cnt = k, rst = _inf;
	_forz(i, n, 1) {
		_fora(j, sg[i].l + 1, sg[i].h - 1) {
			if (dp[i][j] <= _inf) {
				rst = min(rst, dp[i][j]);
			}
		}
		if (rst != _inf)
			break;
		if (sg[i].h <= m)
			cnt--;
	}
	if (cnt == k)
		printf("1\n%d\n", rst);
	else
		printf("0\n%d\n", cnt);
	// printf("\n");
	return 0;
}
