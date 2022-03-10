// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-18 19:42:37.346583

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')
#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (!isdigit(c))
		w = 1 - 2 * (c == '-'), c = getchar();
	while (isdigit(c))
		s = s * 10 + c - '0', c = getchar();
	return s * w;
}

// END OF HEADER

const int P = 998244353, N = 400 + 5;

vi G[N];
int f[N][N], ans[N][N];

int main() {
	ll n = rr(), m = rr();
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; i++)
		f[i][i] = 0;

	for (int i = 0; i < m; i++) {
		int x = rr(), y = rr();
		G[x].push_back(y), G[y].push_back(x);
		f[x][y] = f[y][x] = 1;
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			if (i == k || f[i][k] == 0x3f3f3f3f)
				continue;
			for (int j = 1; j <= n; j++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			ll tans = 1, w = 0;
			for (int k = 1; k <= n; k++) {
				if (f[i][k] + f[j][k] == f[i][j]) {
					w++;
				} else {
					int s = 0;
					for (auto e : G[k]) {
						s += f[i][e] + 1 == f[i][k] && f[e][j] + 1 == f[k][j];
					}
					tans = tans * s % P;
				}
			}
			if (w != f[i][j] + 1) {
				tans = 0;
			}
			ans[i][j] = ans[j][i] = tans;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}

	return 0;
}