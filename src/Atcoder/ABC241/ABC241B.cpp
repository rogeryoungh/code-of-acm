#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int n, m;
	cin >> n >> m;
	multiset<int> s;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		s.insert(t);
	}
	for (int i = 0; i < m; i++) {
		int t;
		cin >> t;
		if (s.count(t) == 0) {
			cout << "No";
			return 0;
		}
		s.erase(s.find(t));
	}
	cout << "Yes";
	return 0;
}
