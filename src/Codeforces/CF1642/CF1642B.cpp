#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (auto &ai : a)
			cin >> ai;

		int m = n;
		sort(a.begin(), a.end());
		for (int i = 1; i < n; i++)
			m -= a[i] == a[i - 1];

		for (int i = 1; i <= n; i++) {
			cout << max(i, m) << " \n"[i == n];
		}
	}
	return 0;
}
