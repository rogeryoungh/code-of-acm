#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int n, m;
	cin >> n >> m;
	int l = 1, r = n;
	while (m--) {
		string t, dir;
		int x;
		cin >> t >> t >> dir >> t >> x;
		if (dir == "left") {
			r = min(r, x - 1);
		} else {
			l = max(l, x + 1);
		}
	}
	if (l > r) {
		cout << -1;
	} else {
		cout << r - l + 1;
	}
	return 0;
}
