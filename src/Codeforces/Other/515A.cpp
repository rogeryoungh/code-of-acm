#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	ll a, b, s;
	cin >> a >> b >> s;
	a = abs(a), b = abs(b);
	if (a + b <= s && (a + b - s) % 2 == 0) {
		cout << "Yes";
	} else {
		cout << "No";
	}
	return 0;
}
