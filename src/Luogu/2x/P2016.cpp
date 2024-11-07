
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <functional>
#include <queue>
#include <stack>
#include <list>

// #include "lab.h"

using namespace std;
typedef long long ll;

#define _fora(i, a, n) for (int i = (a); i <= (n); i++)
#define _forz(i, a, n) for (int i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _ifin(i, min, max) ((((i) - (min)) | ((max) - (i))) >= 0)
#define _ifout(i, min, max) ((((i) - (min)) | ((max) - (i))) < 0)
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)
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
int n, k, i;
const int MN = 1500 + 10;
struct Edge {
	int nxt, too;
} edge[MN * 2];
int head[MN];
int dp[MN][2];
void add(int frm, int too) {
	static int cnt = 0;
	cnt++;
	edge[cnt].too = too;
	edge[cnt].nxt = head[frm];
	head[frm] = cnt;
}
void dfs(int now, int fat) {
	dp[now][1] = 1, dp[now][0] = 0;
	_fore(i, now) {
		if (edge[i].too != fat) {
			dfs(edge[i].too, now);
			dp[now][0] += dp[edge[i].too][1];
			dp[now][1] += min(dp[edge[i].too][0], dp[edge[i].too][1]);
		}
	}
}

int main() {
	n = rr();
	_fora(ti, 1, n) {
		i = rr() + 1;
		k = rr();
		_fora(tj, 1, k) {
			int tr = rr() + 1;
			if (tr == i)
				continue;
			add(i, tr);
			add(tr, i);
		}
	}
	dfs(1, 0);
	int mmin = min(dp[1][0], dp[1][1]);
	printf("%d", mmin);
	// printf("\n");
	return 0;
}
