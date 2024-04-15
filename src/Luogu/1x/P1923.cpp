#include <bits/stdc++.h>
using ll = long long;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))

using namespace std;

ll nn[5000010];

ll k, n;

ll quicksort(ll l, ll r) {
	ll i = l, j = r;
	ll x = nn[(l + r) / 2];
	while (i <= j) {
		while (nn[j] > x)
			j--;
		while (nn[i] < x)
			i++;
		if (i <= j) {
			swap(nn[i], nn[j]);
			i++;
			j--;
		}
	}
	// l<=j<=i<=r
	if (k <= j)
		return quicksort(l, j);
	else if (k >= i)
		return quicksort(i, r);
	else
		return nn[k + 1];
}

int main() {
	scanf("%lld%lld", &n, &k);
	_fora(i, 1, n) {
		scanf("%lld", &nn[i]);
	}
	printf("%lld", quicksort(1, n));
	return 0;
}
