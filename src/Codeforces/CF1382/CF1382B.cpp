#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n, cnt = 0;
		cin >> n;
		bool all_1 = true;
		for (int i = 0; i < n; i++) {
			int a;
			cin >> a;
			if (all_1) {
				if (a != 1)
					all_1 = false;
				else
					cnt++;
			}
		}
		if (all_1)
			cnt++;
		if (cnt % 2 == 0)
			cout << "First\n";
		else
			cout << "Second\n";
	}
	return 0;
}
