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
		vector<int> v(n + 1);
		for (int i = 0; i < n; i++) {
			int t;
			cin >> t;
			int a = min<int>(t - 1, i);
			v[i - a] += 1, v[i + 1] -= 1;
		}
		int now = 0;
		for (int i = 0; i < n; i++) {
			now += v[i];
			cout << (now > 0) << " \n"[i == n - 1];
		}
	}
	return 0;
}
