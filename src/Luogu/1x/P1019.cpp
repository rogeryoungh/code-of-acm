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

char s[30][100];
ll len[30];
ll mt[30][30];
ll n;
int vis[30];

ll dfs(int x) {
	if (vis[x] >= 2)
		return 0;
	vis[x]++;
	ll ml = 0;
	_fora(i, 1, n) {
		if (mt[x][i] > 0) {
			//_dbg("dfs %d -> %lld\n",x, i);
			ll t = dfs(i);
			if (t == 0)
				continue;
			ml = max(ml, t - mt[x][i]);
		}
	}
	vis[x]--;
	return ml + len[x] + 1;
}

void init(int x, int y) {
	ll ml = min(len[x], len[y]);
	_fora(i, 1, ml) {
		int flag = 1;
		_fora(j, 1, i) {
			if (s[x][len[x] + j - i] != s[y][j - 1]) {
				flag = 0;
				//_dbg("%d %d %lld %c %lld %c\n", x, y, i, s[x][len[x]+j-i], j, s[y][j-1]);
				break;
			}
		}
		if (flag) {
			mt[x][y] = i;
			break;
		}
	}
	//_dbg("%d %d %lld\n", x, y, mt[x][y]);
}

int main() {
	n = rr();
	_fora(i, 1, n) {
		scanf("%s", s[i]);
		len[i] = strlen(s[i]) - 1;
	}
	_fora(i, 1, n) {
		_fora(j, 1, n) {
			init(i, j);
		}
	}

	ll ml = 0;

	char c;
	scanf("%s", s[0]);
	c = s[0][0];
	_fora(i, 1, n) {
		if (s[i][0] == c) {
			//_dbg("dfs %d\n", i);
			ll t = dfs(i);
			ml = max(ml, t);
			//_dbg("%lld\n",t);
		}
	}
	printf("%lld\n", ml);

	return 0;
}
