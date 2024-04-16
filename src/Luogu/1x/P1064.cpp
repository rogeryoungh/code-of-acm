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
	int n = rr() / 10;
	int m = rr();
	int vv[70][6], pp[70][6];
	memset(vv, 0, sizeof(vv));
	memset(pp, 0, sizeof(pp));
	int nums[70];
	memset(nums, 0, sizeof(nums));
	int vv1[140];
	memset(vv1, 0, sizeof(vv1));
	_fora(ia, 1, m) {
		int tv = rr() / 10;
		int tp = rr();
		int tq = rr();
		if (tq == 0) {
			vv[ia][1] = tv;
			pp[ia][1] = tp * tv;
			// printf("%d %d\n",vv[ia][1],pp[ia][1]);
		} else {
			int num = 1 << nums[tq];
			_fora(iaa, 1, num) {
				vv[tq][iaa + num] = vv[tq][iaa] + tv;
				pp[tq][iaa + num] = pp[tq][iaa] + tp * tv;
				// printf("%d %d %d\n",iaa+num,vv[tq][iaa+num],pp[tq][iaa+num]);
			}
		}
		nums[tq]++;
	}
	int dp[3210];
	memset(dp, 0, sizeof(dp));
	_fora(ib, 1, m) {
		_forz(iba, n, vv[ib][1]) {
			_fora(ibaa, 1, 1 << nums[ib]) {
				if (iba >= vv[ib][ibaa]) {
					dp[iba] = max(dp[iba], dp[iba - vv[ib][ibaa]] + pp[ib][ibaa]);
					// printf("%d %d %d %d\n",ib,iba,ibaa,dp[iba]);
				}
			}
		}
	}
	int rst = 0;
	_fora(ic, 1, n) {
		rst = max(rst, dp[ic]);
	}
	printf("%d", rst * 10);
	printf("\n");
	return 0;
}
