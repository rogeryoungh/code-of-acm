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
	int n, m;
	cin >> n >> m;
	vector<int> h(n);
	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}
	auto f = [&](int h0) {
		ll sum = 0;
		for (int i = 0; i < n; i++) {
			sum += max(0, h[i] - h0);
		}
		return sum;
	};
	int ret = lower(0, 1E9, [&](int M) {
		return f(M) >= m;
	});
	cout << ret;
	return 0;
}
