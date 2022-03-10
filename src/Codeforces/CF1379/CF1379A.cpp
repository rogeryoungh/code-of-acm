#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

string what = "abacaba";

void solve() {
	int len;
	string s;
	cin >> len >> s;
	for (int i = 0; i < len - 6; i++) {
		string tmp = s;
		for (int j = 0; j < 7; j++)
			if (tmp[i + j] == '?')
				tmp[i + j] = what[j];
		for (auto &c : tmp)
			if (c == '?')
				c = 'z';
		int cnt = 0;
		for (int j = 0; j < len - 6; j++) {
			if (tmp.substr(j, 7) == what)
				cnt++;
		}
		if (cnt == 1) {
			cout << "Yes\n" << tmp << "\n";
			return;
		}
	}
	cout << "No\n";
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
