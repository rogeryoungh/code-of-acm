// GENERATE FROM https://github.com/rogeryoungh/code-of-acm

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
#define _dbg(...) fprintf(stderr, __VA_ARGS__)

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

ll fib[600];

char s[10086], cnt;

void repeat(ll n) {
	while (n--) {
		s[cnt++] = 'A';
	}
	s[cnt++] = 'B';
}

vector<int> ans;

bool dfs(ll x, ll i) {
	if (x == 1)
		return true;
	while (i >= 2) {
		if (x % fib[i] == 0) {
			bool ret = dfs(x / fib[i], i);
			if (ret) {
				ans.push_back(i);
				return true;
			}
		}
		i--;
	}
	return false;
}

int main() {
	fib[0] = fib[1] = 1;
	for (int i = 2; i < 500; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
	ll n = rr(), i = 1;
	while (fib[i] <= n)
		i++;
	bool b = dfs(n, i);
	reverse(ans.begin(), ans.end());
	for (auto &ii : ans) {
		repeat(ii - 1);
	}
	if (b) {
		printf("%s\n", s);
	} else {
		printf("IMPOSSIBLE\n");
	}
	return 0;
}