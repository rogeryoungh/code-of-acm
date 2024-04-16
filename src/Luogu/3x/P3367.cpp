#include <bits/stdc++.h>
using ll = long long;

#define _fora(i, a, n) for (int i = (a); i <= (n); i++)
#define _forz(i, a, n) for (int i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _ifin(i, min, max) if (((i - min) | (max - i)) >= 0)
#define _ifout(i, min, max) if (((i - min) | (max - i)) < 0)
#define ri register int

using namespace std;
typedef long long ll;

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

int f[10010];
int find(int x) {
	if (f[x] == x)
		return x;
	return f[x] = find(f[x]);
}

void merge(int x, int y) {
	f[find(x)] = find(y);
}

int main() {
	int n = rr();
	int m = rr();
	_fora(ia, 1, n) {
		f[ia] = ia;
	}
	_fora(ia, 1, m) {
		if (rr() == 1) {
			merge(rr(), rr());
		} else {
			if (find(rr()) == find(rr()))
				putchar('Y');
			else
				putchar('N');
			printf("\n");
		}
	}
	// printf("\n");
	return 0;
}
