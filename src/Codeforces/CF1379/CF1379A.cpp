#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

string what = "abacaba";
int N = what.length();

void solve() {
	int n;
	string s;
	cin >> n >> s;
	for (int i = 0; i <= n - N; i++) {
		string tmp = s;
		for (int j = 0; j < N; j++) {
			if (tmp[i + j] == '?') {
				tmp[i + j] = what[j];
			}
		}
		for (int j = 0; j < tmp.length(); j++) {
			if (tmp[j] == '?')
				tmp[j] = 'z';
		}
		int cnt = 0;
		for (int j = 0; j <= tmp.length() - N; j++) {
			if (tmp.substr(j, N) == what)
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
