#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

void solve() {
	ll l, r, m;
	cin >> l >> r >> m;
	for (ll a = l; a <= r; a++) {
		int b_c = (m + r - l) % a - (r - l);
		if (b_c > r - l)
			continue;
		if (b_c < 0)
			cout << a << " " << (r + b_c) << " " << r << "\n";
		else
			cout << a << " " << (l + b_c) << " " << l << "\n";
		break;
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
