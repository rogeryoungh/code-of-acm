#pragma region

#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <bits/stdc++.h>
#endif
using namespace std;
typedef long long ll;
typedef long double ld;

#define _lb(x) ((x) & (-x))
#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _in(i, min, max) (((i) - (min)) | ((max) - (i)))
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)
#define _dbg(...) printf(__VA_ARGS__)
#define LN putchar('\n');

inline ll rr() {
	ll s = 0, w = 1;
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

#pragma endregion

ll pp[1005][1005];
bool vis[1005][1005];
bool tp[1005][1005];
ll n, m;

ll pmax;
bool flag;

void dfs(ll x, ll y) {
	if (vis[x][y] || !tp[x][y])
		return;
	if (x == n) {
		flag = true;
		return;
	}
	vis[x][y] = true;
	if (!flag)
		dfs(x + 1, y);
	if (!flag)
		dfs(x, y + 1);
	if (!flag)
		dfs(x, y - 1);
	if (!flag)
		dfs(x - 1, y);
	return;
}

int main() {
	n = rr();
	m = rr();
	ll nmax = 0;
	_fora(i, 1, n) {
		_fora(j, 1, m) {
			ll t = rr();
			pp[i][j] = t;
			nmax = max(nmax, t);
		}
	}

	ll l = 0, r = nmax;

	while (l < r) {
		int mid = (l + r) >> 1;
		pmax = mid;
		memset(tp, 0, sizeof(tp));
		memset(vis, 0, sizeof(vis));
		_fora(i, 1, n) {
			_fora(j, 1, m) {
				if (pp[i][j] <= pmax)
					tp[i][j] = true;
			}
		}
		flag = false;
		dfs(1, 1);
		if (flag)
			r = mid;
		else
			l = mid + 1;
	}
	printf("%lld", l);

	return 0;
}
