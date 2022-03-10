#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	cin >> T;
	while (T--) {
		string s;
		cin >> s;
		vector<int> flag(26);
		bool ans = true;
		for (char si : s) {
			if (si >= 'a') {
				flag[si - 'a'] = true;
			} else {
				if (!flag[si - 'A']) {
					ans = false;
				}
			}
		}
		if (ans)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
