// Problem: C - Slimes
// URL: https://atcoder.jp/contests/abc143/tasks/abc143_c

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int n;
	string s;
	cin >> n >> s;
	s.push_back('$');
	int ans = 0;
	for (int i = 1; i < s.size(); i++) {
		if (s[i] != s[i - 1]) {
			ans += 1;
		}
	}
	cout << ans;
	return 0;
}
