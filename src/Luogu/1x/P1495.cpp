#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

pair<ll, ll> exgcd(ll a, ll b) {
	if (!b) {
		return {1, 0};
	}
	auto [y, x] = exgcd(b, a % b);
	return {x, y - a / b * x};
}

ll inv_mod(ll a, ll p) {
	return (exgcd(a, p).first % p + p) % p;
}

ll crt(const vector<ll> &aa, const vector<ll> &nn) {
	ll prod = 1, ret = 0, n = aa.size();
	for (ll ni : nn)
		prod *= ni;
	for (int i = 0; i < n; i++) {
		ll m = prod / nn[i];
		ret = (ret + aa[i] * m * inv_mod(m, nn[i])) % prod;
	}
	return ret;
}

int main() {
	int n;
	cin >> n;
	vector<ll> aa(n), nn(n);
	for (int i = 0; i < n; i++) {
		cin >> nn[i] >> aa[i];
	}
	cout << crt(aa, nn);
	return 0;
}
