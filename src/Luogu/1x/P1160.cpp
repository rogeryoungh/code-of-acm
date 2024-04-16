#include <bits/stdc++.h>
using ll = long long;

using namespace std;
#define _fora(i, a, n) for (int i = (a); i <= (n); i++)
#define _forz(i, a, n) for (int i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))

inline int rr() {
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}

struct List {
	int prev, next;
} l[100010];

void lst_delete(int id) {
	if (l[id].prev == 0)
		return;
	l[l[id].prev].next = l[id].next;
	l[l[id].next].prev = l[id].prev;
	l[id].next = l[id].prev = 0;
}

void lst_add(int id, int p) {
	l[id].next = l[p].next;
	l[l[p].next].prev = id;
	l[id].prev = p;
	l[p].next = id;
}

int main() {
	int n = rr();
	int p;
	l[0].next = 1;
	l[1].prev = 0;
	_fora(ia, 2, n) {
		int k = rr();
		int p = rr();
		if (p == 1) {
			lst_add(ia, k);
		} else {
			lst_add(ia, l[k].prev);
		}
	}
	int m = rr();
	_fora(ia, 1, m) {
		lst_delete(rr());
	}
	p = l[0].next;
	while (l[p].next) {
		printf("%d ", p);
		p = l[p].next;
	}
	printf("%d\n", p);
	return 0;
}
