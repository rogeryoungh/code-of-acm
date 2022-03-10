#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (auto &vi : v)
		cin >> vi;
	for (int i = 0; i < n; i++) {
		int m1, m2;
		if (i == 0) {
			m1 = v[1] - v[i], m2 = v[n - 1] - v[i];
		} else if (i == n - 1) {
			m2 = v[i] - v[0], m1 = v[i] - v[i - 1];
		} else {
			m1 = min(v[i] - v[i - 1], v[i + 1] - v[i]);
			m2 = max(v[i] - v[0], v[n - 1] - v[i]);
		}
		cout << m1 << " " << m2 << "\n";
	}
	return 0;
}
