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
		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			v[i] = i + 1;
		}
		swap(v[1], v[2]);
		auto judge = [&]() {
			for (int i = 2; i < n; i++) {
				if (v[i] == v[i - 1] + v[i - 2])
					return false;
			}
			return true;
		};

		int cnt = 0;
		do {
			if (judge()) {
				cnt++;
				for (auto vi : v)
					cout << vi << " ";
				cout << "\n";
				if (cnt == n)
					break;
			}
		} while (next_permutation(v.begin(), v.end()));
	}
	return 0;
}
