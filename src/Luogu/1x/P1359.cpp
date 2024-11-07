
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
const int MN = 200 + 10;
int adj[MN][MN], n, dis[MN];

void bellman_ford(int ss) {
	memset(dis, 0x3f, sizeof(dis));
	dis[ss] = 0;
	_fora(ia, 1, n - 1) {
		_fora(i, 1, n) {
			_fora(j, i + 1, n) {
				dis[j] = min(dis[j], dis[i] + adj[i][j]);
			}
		}
	}
}

int main() {
	n = rr();
	_fora(i, 1, n) {
		_fora(j, i + 1, n) {
			if (i == j)
				continue;
			adj[j][i] = adj[i][j] = rr();
		}
	}
	bellman_ford(1);
	printf("%d", dis[n]);
	// printf("\n");
	return 0;
}
