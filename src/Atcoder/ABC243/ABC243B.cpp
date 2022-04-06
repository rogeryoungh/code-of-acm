#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (auto &ai : a)
		cin >> ai;
	for (auto &bi : b)
		cin >> bi;
	int ans1 = 0;
	for (int i = 0; i < n; i++)
		ans1 += a[i] == b[i];
	int ans2 = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j == i)
				continue;
			ans2 += a[i] == b[j];
		}
	}
	cout << ans1 << "\n" << ans2;
	return 0;
}
