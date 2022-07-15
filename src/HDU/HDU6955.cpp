// GENERATE FROM https://github.com/rogeryoungh/code-of-acm

// Problem: Xor sum
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/showproblem.php?pid=6955
// Date: 2021-10-09 20:02:59
//
// Powered by CP Editor (https://cpeditor.org)

#define RYLOCAL

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')

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

// END OF HEADER

const int maxn = 1e5 + 10, o = 30 - 1;

int trie[maxn * 30][2], val[maxn * 30], tot;

void insert(int ai, int i) {
	int p = 1;
	for (int j = o; j >= 0; j--) {
		int ch = (ai >> j) & 1;
		if (trie[p][ch] == 0)
			trie[p][ch] = ++tot;
		p = trie[p][ch];
		val[p] = i;
	}
}

int n, k;

int search(int ai, int i) {
	int p = 1, res = -1;
	for (int j = o; j >= 0; j--) {
		int x1 = (k >> j) & 1, x2 = (ai >> j) & 1;
		if (x1 == 0) {
			int tp = trie[p][x2 ^ 1];
			if (tp > 0)
				res = max(res, val[tp]);
		}
		p = trie[p][x1 ^ x2];
		if (p == 0)
			break;
	}
	if (p > 0) {
		res = max(res, val[p]);
	}
	return res;
}

int main() {
	int ttt = rr();
	while (ttt--) {
		n = rr(), k = rr();
		tot = 1;

		int anl = -1, anr = n + 1, pre_sum = 0;

		memset(trie, 0, sizeof(int) * 2 * o * n);
		for (int i = 1; i <= n; i++) {
			int ai = pre_sum ^ rr();
			int res = search(ai, i);
			if (res >= 0 && i - res < anr - anl)
				anl = res, anr = i;
			insert(ai, i);
			pre_sum = ai;
		}
		if (anl >= 0)
			printf("%d %d\n", anl + 1, anr);
		else
			printf("-1\n");
	}
	return 0;
}
