#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n), b(n);
	for (auto &ai : a) {
		cin >> ai;
	}
	for (auto &bi : b) {
		cin >> bi;
	}
	using pii = pair<int, int>;
	vector<pii> v(n);
	for (int i = 0; i < n; i++) {
		v[i] = {a[i] - b[i], i};
	}
	sort(v.begin(), v.end());
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		int id = v[i].second;
		ans += (i < k || v[i].first < 0) ? a[id] : b[id];
	}
	cout << ans;
	return 0;
}

