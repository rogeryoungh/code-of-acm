#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <functional>
#include <queue>
#include <stack>
#include <list>
#include <map>
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

void pr(ll n) {
	char c = n % 10 + '0';
	if (n >= 10)
		pr(n / 10);
	putchar(c);
}
#ifdef RYLOCAL
#include "lab.hpp"
#endif

bool next(ll *aa, ll n) {
	int i = n - 2;
	while (aa[i] >= aa[i + 1] && i >= 0)
		i--;
	if (i < 0) {
		reverse(aa, aa + n);
		return false;
	} else {
		ll j = i + 1;
		while (aa[i] < aa[j] && j < n)
			j++;
		swap(aa[j - 1], aa[i]);
		reverse(aa + i + 1, aa + n);
		return true;
	}
}

ll aa[10086];

int main() {
	int n = rr();
	_fora(i, 1, n) {
		aa[i - 1] = i;
	}
	do {
		_fora(i, 1, n) {
			printf("%5lld", aa[i - 1]);
		}
		printf("\n");
	} while (next(aa, n));
	return 0;
}
