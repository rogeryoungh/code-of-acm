#include <bits/stdc++.h>
using ll = long long;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))

using namespace std;

int main() {
	ll n;
	scanf("%lld", &n);
	ll nn[310];
	nn[0] = 0;
	_fora(i, 1, n) {
		scanf("%lld", &nn[i]);
	}
	sort(nn + 1, nn + n + 1);
	ll l = 0, r = n;
	ll sum = 0;
	while (l < r) {
		sum += (nn[l] - nn[r]) * (nn[l] - nn[r]) + (nn[l + 1] - nn[r]) * (nn[l + 1] - nn[r]);
		l++;
		r--;
	}
	printf("%lld\n", sum);
	return 0;
}
