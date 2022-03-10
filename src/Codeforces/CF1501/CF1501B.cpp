// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-27 22:21:14.805857

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
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

int main() {
	int T = rr();
	while (T--) {
		int n = rr();
		vector<int> v(n + 1);
		for (int i = 0; i < n; i++) {
			int a = min<int>(rr() - 1, i);
			v[i - a] += 1, v[i + 1] -= 1;
		}
		int now = 0;
		for (int i = 0; i < n; i++) {
			now += v[i];
			printf("%d ", now > 0);
		}
		printf("\n");
	}
	return 0;
}