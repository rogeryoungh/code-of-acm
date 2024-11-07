#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <bits/stdc++.h>
#endif

using namespace std;
typedef long long ll;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _in(i, min, max) (((i) - (min)) | ((max) - (i)))
#define _dbg(...) printf(__VA_ARGS__)

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

ll s[40][40];
int vis[40][40];
ll n;

void dfs(ll x, ll y) {
	if (vis[x][y] || _in(x, 1, n) < 0 || _in(y, 1, n) < 0)
		return;
	vis[x][y] = 1;
	if (s[x][y] == 1)
		return;
	s[x][y] = 3;
	dfs(x - 1, y);
	dfs(x + 1, y);
	dfs(x, y - 1);
	dfs(x, y + 1);
}

int main() {
	n = rr();
	_fora(i, 1, n) {
		_fora(j, 1, n) {
			s[i][j] = rr();
		}
	}
	ll l = 2, r = n - 1;
	_fora(i, 1, n) {
		if (s[1][i] == 0)
			dfs(1, i);
		if (s[n][i] == 0)
			dfs(n, i);
		if (s[i][1] == 0)
			dfs(i, 1);
		if (s[i][n] == 0)
			dfs(i, n);
	}
	_fora(i, 1, n) {
		_fora(j, 1, n) {
			if (j != 1)
				putchar(' ');
			if (s[i][j] == 0)
				putchar('2');
			else if (s[i][j] == 1)
				putchar('1');
			else
				putchar('0');
		}
		putchar('\n');
	}
	return 0;
}
