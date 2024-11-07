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

int num[260];
int dp[260][260];
int n;

int main() {
	n = rr();
	_fora(i, 1, n) {
		num[i] = rr();
		dp[i][num[i]] = i + 1;
	}

	int rst = 0;
	_fora(j, 2, 60) {
		_fora(i, 1, n) {
			if (!dp[i][j])
				dp[i][j] = dp[dp[i][j - 1]][j - 1];
			if (dp[i][j])
				rst = max(rst, j);
		}
	}
	printf("%d", rst);
	printf("\n");
	return 0;
}
