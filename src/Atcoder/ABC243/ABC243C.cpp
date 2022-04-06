#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

using int3 = tuple<int, int, int>;

int main() {
	int n;
	cin >> n;
	vector<int> x(n), y(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	string s;
	cin >> s;

	vector<int3> v(n + 1);
	for (int i = 0; i < n; i++) {
		v[i] = {x[i], y[i], s[i]};
	}
	v[n] = {-1, -1, -1};
	sort(v.begin(), v.end(), [](int3 a, int3 b) {
		return std::get<1>(a) < std::get<1>(b);
	});

	int l = -2E9, r = 2E9;
	for (int i = 0; i < n - 1; i++) {
		auto [x1, y1, s1] = v[i];
		auto [x2, y2, s2] = v[i + 1];
		if (y1 != y2) {
			l = -2E9, r = 2E9;
		}
		if (s2 == 'L') {
			l = max(l, x2);
		} else {
			r = min(r, x2);
		}
		if (l > r) {
			cout << "Yes";
			exit(0);
		}
	}
	cout << "No";
	return 0;
}
