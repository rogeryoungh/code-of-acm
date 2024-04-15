#include <bits/stdc++.h>
using ll = long long;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))

using namespace std;

string read() {
	string s = "";
	string s1 = "";
	char c;
	while (cin >> c) {
		if (c == '[') {
			int n;
			cin >> n;
			string ss = read();
			string sa = "";
			while (n--)
				sa += ss;
			s += sa;
		} else if (c == ']') {
			return s;
		} else {
			s += c;
		}
	}
	return s;
}

int main() {
	cout << read();
	return 0;
}
