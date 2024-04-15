#include <bits/stdc++.h>
using ll = long long;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))

using namespace std;

ll dp[110];
ll a[110];

int main() {
	ll m, n;
	scanf("%lld%lld", &n, &m);
	dp[0] = 1;
	_fora(i, 1, n) {
		scanf("%lld", &a[i]);
	}
	_fora(i, 1, n) {
		_forz(j, m, 0) {
			_fora(k, 1, min(j, a[i])) {
				dp[j] = (dp[j] + dp[j - k]) % 1000007;
			}
		}
	}
	printf("%lld\n", dp[m]);
	return 0;
}