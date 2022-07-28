#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

template <class Comp> // last true
ll lower(ll l, ll r, Comp check) {
	if (not check(l))
		return r;
	while (r - l > 1) {
		ll m = l + (r - l) / 2;
		(check(m) ? l : r) = m;
	}
	return l;
}

template <class Comp> // first true
ll upper(ll l, ll r, Comp check) {
	if (not check(r - 1))
		return r;
	while (r - l > 1) {
		ll m = l + (r - l) / 2;
		(check(m - 1) ? l : r) = m;
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
	const int offset = 1E5;
	auto f = [&](int h0) {
		h0 += offset;
		ll sum = 0;
		for (int i = 0; i < n; i++) {
			sum += max(0, h[i] - h0);
		}
		return sum;
	};
	int ret = lower(0 - offset, 1E9 - offset,
					[&](int M) {
						return f(M) >= m;
					}) +
			  offset;
	cout << ret;
	return 0;
}
