#include <bits/stdc++.h>
using ll = long long;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))

using namespace std;

int dp[1000000];

int main() {
	int n;
	scanf("%d", &n);
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 5;
	_fora(i, 4, n) {
		dp[i] = (dp[i - 1] * 2 + dp[i - 3]) % 10000;
	}
	printf("%d\n", dp[n]);
	return 0;
}
