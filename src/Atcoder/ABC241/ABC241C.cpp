#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int n;
	cin >> n;
	vector<string> m(n);
	for (auto &mi : m) {
		cin >> mi;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			auto sharp = [&](int x, int y) {
				int ti = i, tj = j;
				int sum = 0;
				for (int u = 0; u < 6; u++) {
					if (ti < 0 || tj < 0 || ti >= n || tj >= n) {
						return false;
					}
					sum += m[ti][tj] == '#';
					ti += x, tj += y;
				}
				return sum >= 4;
			};

			bool flag = false;
			flag = flag || sharp(1, 0) || sharp(1, 1) || sharp(0, 1) || sharp(-1, 1);
			flag = flag || sharp(-1, 0) || sharp(-1, -1) || sharp(0, -1) || sharp(1, -1);
			if (flag) {
				cout << "Yes";
				return 0;
			}
		}
	}
	cout << "No";
	return 0;
}
