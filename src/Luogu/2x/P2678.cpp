#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

template <class Comp>
ll lower(ll l, ll r, Comp check) {
	while (l < r) {
		ll m = (l + r + 1) / 2;
		if (check(m))
			l = m;
		else
			r = m - 1;
	}
	return l;
}

template <class Comp>
ll upper(ll l, ll r, Comp check) {
	while (l < r) {
		ll m = (l + r) / 2;
		if (check(m))
			r = m;
		else
			l = m + 1;
	}
	return l;
}

int main() {
	int len, n, m;
	cin >> len >> n >> m;
	vector<int> d(n + 2);
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
	}
	d[0] = 0, d[n + 1] = len;
	auto f = [&](int x) {
		int u = 0, l = 0, r = 0;
		while (r < d.size()) {
			if (d[r] - d[l] >= x) {
				l = r;
			} else {
				u += r != l;
			}
			r++;
		}
		return u;
	};
	int ret = lower(1, len, [&](int M) {
		return f(M) <= m;
	});
	cout << ret;
	return 0;
}
