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
	int tsh, tsm, teh, tem;
	scanf("%d:%d%d:%d", &tsh, &tsm, &teh, &tem);
	int tsum = (teh - tsh) * 60 + tem - tsm;
	int n = rr();

	ll tt[100010], cc[100010];
	int tp = 1;
	_fora(ia, 1, n) {
		int t = rr();
		int c = rr();
		int p = rr();
		if (p == 1) {
			tt[tp] = t;
			cc[tp] = c;
			// printf("%d %d %d\n",tp,tt[tp],cc[tp]);
			tp++;
		} else {
			if (p == 0)
				p = 99999;
			int b = 1;
			while (b < p) {
				tt[tp] = t * b;
				cc[tp] = c * b;
				// printf("%d %d %d\n",tp,tt[tp],cc[tp]);
				p -= b;
				b *= 2;
				tp++;
			}
			tt[tp] = t * p;
			cc[tp] = c * p;
			tp++;
		}
	}
	ll dp[1010];
	memset(dp, 0, sizeof(dp));
	dp[0] = 0;
	_fora(ib, 1, tp - 1) {
		_forz(iba, tsum, tt[ib]) {
			dp[iba] = max(dp[iba], dp[iba - tt[ib]] + cc[ib]);
			// printf("%d %d %d\n",ib,iba,dp[iba]);
		}
	}
	ll rst = 0;
	_fora(ic, 0, tsum) {
		rst = max(dp[ic], rst);
	}
	printf("%lld", rst);
	printf("\n");
	return 0;
}
