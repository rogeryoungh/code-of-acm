#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

using i128 = __int128_t;

std::tuple<ll, ll, ll> exgcd(ll a, ll b) {
	if (!b) {
		return {1, 0, a};
	}
	auto [y, x, g] = exgcd(b, a % b);
	return {x, y - a / b * x, g};
}

ll excrt(const vector<ll> &aa, const vector<ll> &nn) {
	ll ans = aa[0], M = nn[0];
	for (int i = 1; i < aa.size(); i++) {
		if (M % nn[i] == 0 && ans % nn[i] == aa[i])
			continue;
		ll B = (aa[i] - ans % nn[i] + nn[i]) % nn[i];
		auto [x, y, gcd] = exgcd(M, nn[i]);
		x = (i128)x * (B / gcd) % nn[i];
		ans += M * x;
		M *= nn[i] / gcd;
		ans = (ans + M) % M;
	}
	return ans;
}

int main() {
	int n;
	cin >> n;
	vector<ll> aa(n), nn(n);
	for (int i = 0; i < n; i++) {
		cin >> nn[i] >> aa[i];
	}
	cout << excrt(aa, nn);

	return 0;
}
