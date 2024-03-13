#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

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

void pr(ll n) {
	if (n > 9)
		pr(n / 10);
	putchar(n % 10 + '0');
}

ll mtx[10][10], dp[10][10];

int main() {
	ll N = rr();
	while (true) {
		ll a = rr(), b = rr(), c = rr();
		if (a + b + c == 0)
			break;
		mtx[a][b] = c;
	}

	for (ll ss = 2; ss <= 2 * N; ss++) {
		ll max_x1 = min(N, ss - 1), min_x1 = max(1ll, ss - N);
		for (ll x1 = max_x1; x1 >= min_x1; x1--) {
			ll max_x2 = min(N, ss - 1), min_x2 = max(1ll, ss - N);
			for (ll x2 = max_x2; x2 >= min_x2; x2--) {
				dp[x1][x2] = max({
					dp[x1 - 1][x2 - 1],
					dp[x1][x2 - 1],
					dp[x1 - 1][x2],
					dp[x1][x2]
				});
				dp[x1][x2] += mtx[x1][ss - x1] + mtx[x2][ss - x2];
				if (x1 == x2)
					dp[x1][x2] -= mtx[x1][ss - x1];
			}
		}
	}
	printf("%lld\n", dp[N][N]);
	return 0;
}
