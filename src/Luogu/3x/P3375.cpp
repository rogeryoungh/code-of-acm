#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

auto pre_kmp(string s) {
	int n = s.length();
	vector<int> pi(n + 1);
	for (int i = 1; i < n; i++) {
		int j = pi[i];
		while (j > 0 && s[i] != s[j]) {
			j = pi[j];
		}
		pi[i + 1] = j + (s[i] == s[j]);
	}
	return pi;
}

void kmp(string s, string t) {
	auto pi = pre_kmp(s);
	int p = 0, n = t.length(), sn = s.length();
	for (int i = 0; i < n; i++) {
		int j = p;
		while (j > 0 && t[i] != s[j]) {
			j = pi[j];
		}
		p = j + (t[i] == s[j]);
		if (p == sn) {
			cout << i - sn + 2 << "\n";
		}
	}
	for (int i = 1; i <= sn; i++) {
		cout << pi[i] << " ";
	}
}

int main() {
	string s, t;
	cin >> t >> s;
    kmp(s, t);

	return 0;
}