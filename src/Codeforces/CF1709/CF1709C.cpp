#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

string solve1(const string &s) {
	string ret = s;
	int a = 0, b = 0, x = 0;
	for (auto si : s) {
		a += si == '(';
		b += si == ')';
		x += si == '?';
	}
	int n = s.length(), dep = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			a--;
			dep++;
		} else if (s[i] == ')') {
			b--;
			dep--;
		} else if (s[i] == '?') {
			if (a + dep == x + b) {
				ret[i] = ')';
				dep--;
			} else {
				ret[i] = '(';
				dep++;
			}
			x--;
		}
	}
	return ret;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		string s;
		cin >> s;

		string ret = solve1(s);
		// cout << ret << endl;

		int n = s.length();
		vector<int> v(n + 1);

		int past_min = -1E9, past = -1;
		bool f = true;
		for (int i = 0; i < n; i++) {
			v[i] = ret[i] == '(' ? 1 : -1;
			if (i > 0)
				v[i] += v[i - 1];
			// cout  << v[i] << ' ' << past_min << ' ' << past << endl;
			if (s[i] == '?') {
				if (past_min >= 2 && ret[past] != ret[i]) {
					f = false;
					break;
				} else {
					past_min = v[i];
				}
				past = i;
			}
			past_min = min(v[i], past_min);
		}

		cout << (f ? "YES" : "NO") << endl;
	}
	return 0;
}
