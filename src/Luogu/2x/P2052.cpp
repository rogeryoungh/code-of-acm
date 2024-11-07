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
const int MN = 1000010;
struct Edge {
	int to, nxt, len;
} edge[MN * 2];
int head[MN];
int n;
ll rst;

void add(int frm, int to, int len) {
	// printf("%d %d %d\n",frm,to,len);
	static int cnt = 0;
	++cnt;
	edge[cnt].to = to;
	edge[cnt].nxt = head[frm];
	head[frm] = cnt;
	edge[cnt].len = len;
}
int siz[MN];
void dfs(int x, int fa) {
	siz[x] = 1;
	// printf("%d %d\n",x,fa);
	for (int i = head[x]; i != 0; i = edge[i].nxt) {
		if (edge[i].to != fa) {
			dfs(edge[i].to, x);
			ll ans = abs(n - 2 * siz[edge[i].to]);
			rst += ans * edge[i].len;
			siz[x] += siz[edge[i].to];
		}
	}
}

int main() {
	n = rr();
	_fora(ia, 1, n - 1) {
		int ta = rr();
		int tb = rr();
		int tc = rr();
		add(ta, tb, tc);
		add(tb, ta, tc);
	}
	dfs(1, 1);
	printf("%lld", rst);
	// printf("\n");
	return 0;
}
