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
		for (int i = n; i >= 1; i--) {
			v[i] = n - i + 1;
		}
		for (int i = n; i >= 1; i--) {
			for (int j = 1; j <= n; j++)
				cout << v[j] << " \n"[j == n];
			swap(v[i - 1], v[i]);
		}
	}
	return 0;
}
