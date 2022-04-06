#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

auto pre_exkmp(const string &s) {
	int l = 0, r = 0, n = s.length();
	vector<int> zz(n);
	zz[0] = n;
	for (int i = 1; i < n; i++) {
		if (i < r) {
			zz[i] = min(r - i, zz[i - l]);
		}
		while (i + zz[i] < n && s[zz[i]] == s[i + zz[i]]) {
			zz[i]++;
		}
		if (i + zz[i] > r) {
			l = i, r = i + zz[i];
		}
	}
	return zz;
}

void exkmp(const string &s, const string &t) {
	auto zz = pre_exkmp(s);
	ll ans1 = 0, ans2 = 0;
	for (int i = 0; i < s.length(); i++) {
		ans1 ^= 1ll * (i + 1) * (zz[i] + 1);
	}

	int l = 0, r = 0, n = t.length();
	for (int i = 0; i < n; i++) {
		int p = 0;
		if (i < r) {
			p = min(r - i, zz[i - l]);
		}
		while (i + p < n && s[p] == t[i + p]) {
			p++;
		}
		if (i + p > r) {
			l = i, r = i + p;
		}
		ans2 ^= 1ll * (i + 1) * (p + 1);
	}
	cout << ans1 << "\n" << ans2;
}

int main() {
	string s, t;
	cin >> t >> s;
	exkmp(s, t);
	return 0;
}