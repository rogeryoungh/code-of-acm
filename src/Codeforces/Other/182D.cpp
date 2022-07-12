#include <bits/stdc++.h>
#define IOS                  \
	ios::sync_with_stdio(0); \
	cin.tie(0);              \
	cout.tie(0);
using namespace std;
const int N = 1e6 + 7;
typedef unsigned long long ULL;
string s1, s2;
int n1, n2;

bool check(const string &s, const string &t) {
	int l1 = s.length(), l2 = t.length();
	if (l2 % l1 != 0) {
		return false;
	}
	for (int i = 0; i < l2; i++) {
		if (s[i % l1] != t[i % l2]) {
			return false;
		}
	}
}
bool check(string s) {
	string now = s;
	int len = s.size();
	if (n1 % len || n2 % len)
		return 0;
	if (ch != s1)
		return 0;
	return mul(s, n2 / len) == s2;
}
int main() {
	IOS cin >> s1 >> s2;
	n1 = s1.size(), n2 = s2.size();
	s1 = s1, s2 = s2;
	int ans = 0;
	string s;
	for (int i = 0; i < n1; i++) {
		s += s1[i];
		ans += check(s);
	}
	cout << ans << endl;
	return 0;
}