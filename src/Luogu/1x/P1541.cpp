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

int max4(int a, int b, int c, int d) {
	return max(max(a, b), max(c, d));
}

ll dp[42][42][42];

int main() {
	int n = rr();
	int m = rr();
	int nn[352];
	_fora(ia, 1, n) {
		nn[ia] = rr();
	}
	int tt[5] = {0};
	_fora(ia, 1, m) {
		tt[rr()]++;
	}
	memset(dp, 0, sizeof(dp));
	_fora(ia, 0, tt[1]) {
		_fora(ib, 0, tt[2]) {
			_fora(ic, 0, tt[3]) {
				_fora(id, 0, tt[4]) {
					dp[ib][ic][id] = nn[ia * 1 + ib * 2 + ic * 3 + id * 4 + 1] +
													 max4(ib == 0 ? 0 : dp[ib - 1][ic][id], ic == 0 ? 0 : dp[ib][ic - 1][id],
																id == 0 ? 0 : dp[ib][ic][id - 1], dp[ib][ic][id]);
					// printf("%d %d %d %d %d\n",ia,ib,ic,id,dp[ib][ic][id]);
				}
			}
		}
	}

	printf("%lld", dp[tt[2]][tt[3]][tt[4]]);
	printf("\n");
	return 0;
}