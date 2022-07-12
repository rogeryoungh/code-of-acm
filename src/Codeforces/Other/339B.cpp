#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int n, m;
	cin >> n >> m;
	int now = 1;
	ll ans = 0;
	for (int i = 0; i < m; i++) {
		int ai;
		cin >> ai;
		if (ai >= now) {
			ans += ai - now;
		} else {
			ans += ai + n - now;
		}
		now = ai;
	}
	cout << ans;
	return 0;
}
