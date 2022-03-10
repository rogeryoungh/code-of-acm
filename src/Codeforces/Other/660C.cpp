#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	int L = 0, R = -1, sum0 = 0;
	int tl = 0, tr = -1;
	for (int i = 0; i < n; i++) {
		if (v[i] == 0) {
			sum0++;
			while (sum0 > k) {
				sum0 -= v[tl++] == 0;
			}
		}
		tr = i;
		if (tr - tl > R - L) {
			L = tl, R = tr;
		}
	}
	int ans = R - L + 1;
	cout << ans << "\n";
	fill_n(v.begin() + L, ans, 1);
	for (auto vi : v) {
		cout << vi << " ";
	}
	return 0;
}
