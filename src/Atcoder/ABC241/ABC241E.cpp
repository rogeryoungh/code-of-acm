#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	ll n, k;
	cin >> n >> k;
	vector<ll> v(n), vis(n);
	for (auto &vi : v)
		cin >> vi;

	auto get = [&](ll u, const ll p = 0) {
		ll ans = p, pos = p % n;
		while (u--) {
			ans += v[pos];
			pos = ans % n;
		}
		return ans - p;
	};

	ll cnt = 0, pos = 0, tsum = 0;
	while (!vis[pos]) {
		vis[pos] = cnt++;
		tsum += v[pos];
		pos = tsum % n;
	}
	ll crc = cnt - vis[pos], left = k - vis[pos];
	ll ans = 0;
	if (left < 0) {
		ans += get(k);
	} else {
		ans = get(crc, pos) * (left / crc) + get(vis[pos] + left % crc);
	}
	cout << ans;
	return 0;
}
