#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

#define x first
#define y second

using pii = pair<int, int>;

template <class Comp> // first true
ll upper(ll l, ll r, Comp check) {
	if (!check(r))
		return r + 1;
	while (l < r) {
		ll m = (l + r) / 2;
		if (check(m))
			r = m;
		else
			l = m + 1;
	}
	return l;
}

void solve() {
	int n, m;
	cin >> n >> m;
	vector<pii> v(m + 1);
	for (int i = 1; i <= m; i++) {
		cin >> v[i].x >> v[i].y;
	}
	sort(v.begin() + 1, v.end());
	vector<ll> sum(m + 1);
	for (int i = 1; i <= m; i++) {
		sum[i] = sum[i - 1] + v[i].x;
	}
	ll ans = 0;
	for (int i = 1; i <= m; i++) {
		int pos = upper(1, m, [&](int M) {
			return v[M].x > v[i].y;
		});
		int num = m - pos + 1;
		if (num <= n) {
			ll tans = sum[m] - sum[pos - 1] + (n - num) * v[i].y;
			if (pos > i) {
				tans += v[i].x - v[i].y;
			}
			ans = max(ans, tans);
		} else {
			ans = max(ans, sum[m] - sum[max(0, m - n)]);
		}
	}
	cout << ans << "\n";
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
