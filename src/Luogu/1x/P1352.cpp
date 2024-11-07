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

int r[6010];
int head[6010];
int flag[6010];

int dfs(int s) {
	if (flag[s] == 0)
		flag[s] = -dfs(head[s]);
	return flag[s];
}

int main() {
	int n = rr();
	int sum = n * (n + 1) / 2;
	_fora(ia, 1, n) {
		r[ia] = rr();
	}
	_fora(ia, 1, n - 1) {
		int t = rr();
		sum -= t;
		head[t] = rr();
	}
	flag[sum] = 1;
	int s0, s1;
	s0 = s1 = 0;
	_fora(i, 1, n) {
		dfs(i);
		// printf("%d %d %d %d\n",i,flag[i],s0,s1);
		if (r[i] < 0)
			continue;
		if (flag[i] == 1)
			s1 += r[i];
		else
			s0 += r[i];
	}
	printf("%d", max(s0, s1));
	// printf("\n");
	return 0;
}
