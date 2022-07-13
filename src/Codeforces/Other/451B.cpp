// Problem: B. Sort the Array
// URL: https://codeforces.com/problemset/problem/451/B

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int n;
	cin >> n;
	vector<ll> v(n + 2);
	v[0] = -1, v[n + 1] = 1E9 + 9;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	vector<int> pos;
	for (int i = 1; i <= n; i++) {
		if ((v[i] - v[i - 1]) * (v[i + 1] - v[i]) < 0) {
			pos.push_back(i);
		}
	}
	if (pos.size() == 0) {
		cout << "yes\n1 1";
	} else if (pos.size() == 1) {
		cout << "yes\n1 " << pos[0];
	} else if (pos.size() == 2) {
		int l = pos[0], r = pos[1];
		std::reverse(v.begin() + l, v.begin() + r + 1);
		if (std::is_sorted(v.begin(), v.end())) {
			cout << "yes\n" << l << " " << r;
		} else {
			cout << "no";
		}
	} else {
		cout << "no";
	}

	return 0;
}
