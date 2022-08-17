#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

int ____ = cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

const int M = 1E6;

int main() {
	int n;
	cin >> n;
	vector<int> a(n), v(M + 1);
	ll asum = 0;
	for (auto &ai : a) {
		cin >> ai;
		v[ai]++;
		asum += ai;
	}
	for (int i = 1; i <= M; i++) {
		v[i] += v[i - 1];
	}
	ll ans = 1E15;
	for (int x = 1; x <= M; x++) {
		ll sum = 0;
		for (int i = 1; i <= M / x; i++) {
			int l = i * x - 1 , r = (i + 1) * x - 1;
			r = min(r, M);
			sum += 1ll * (v[r] - v[l]) * i;
		}
		sum = asum - sum * (x - 1);
		ans = min(ans, sum);
	}
	cout << ans;

	return 0;
}
