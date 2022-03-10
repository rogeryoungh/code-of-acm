#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

const int P = 998244353;
using pll = pair<ll, ll>;

vector<pll> factor(ll n) {
	vector<pll> ret;
	for (ll i = 2; 1ll * i * i <= n; i++) {
		int cnt = 0;
		while (n % i == 0) {
			n /= i, cnt++;
		}
		if (cnt > 0) {
			ret.push_back({i, cnt});
		}
	}
	if (n > 1) {
		ret.push_back({n, 1});
	}
	return ret;
}

int main() {
	ll pp, ans = 1;
	cin >> pp;
	for (auto [p, e] : factor(pp - 1)) {
		ll pk = 1, tsum = 1;
		p %= P;
		for (int k = 1; k <= e; k++) {
			tsum += 1ll * pk * pk % P * (p - 1) % P * p % P;
			pk = 1ll * pk * p % P;
		}
		ans = 1ll * ans * tsum % P;
	}
	cout << (ans + 1) % P;
	return 0;
}
