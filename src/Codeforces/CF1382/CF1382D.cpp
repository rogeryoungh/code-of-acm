// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2022-01-22 23:08:23.231384

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define _dbg(...)
#define dbg(x)

ll rr() {
	ll s = 0, w = false, c = getchar();
	for (; !isdigit(c); c = getchar())
		w = w || c == '-';
	for (; isdigit(c); c = getchar())
		s = s * 10 + c - '0';
	return w ? -s : s;
}

// END OF HEADER

int main() {
	int T = rr();
	while (T--) {
		int n = rr();
		vi P(n * 2 + 1), v, dp(n + 1);
		for (int i = 0; i < n * 2; i++)
			P[i] = rr();
		int m = 0;
		for (int i = 1; i < n * 2 + 1; i++) {
			if (P[i] > P[m]) {
				v.push_back(i - m);
				m = i;
			}
		}
		for (auto vi : v) {
			for (int j = n; j >= vi; j--) {
				dp[j] = max(dp[j], dp[j - vi] + vi);
			}
		}
		if (dp[n] == n)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}