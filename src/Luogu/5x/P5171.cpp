#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

ll floor_sum(ll a, ll b, ll c, ll n) {
	ll m = (a * n + b) / c, S1 = n * (n + 1) / 2;
	if (a == 0) {
		return b / c * (n + 1);
	} else if (a >= c || b >= c) {
		ll f = S1 * (a / c) + b / c * (n + 1);
		return f + floor_sum(a % c, b % c, c, n);
	} else {
		return m * n - floor_sum(c, c - b - 1, a, m - 1);
	}
}

int main() {
    ll a , b , c ;
	cin >> a >> b >> c;
    ll n = c / a;
	ll ans = floor_sum(a, c - a * n, b, n) + n + 1;
    cout << ans;
	return 0;
}
