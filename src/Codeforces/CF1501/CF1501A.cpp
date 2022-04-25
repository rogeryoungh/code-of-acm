#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	cin >> T;
	while (T--) {
		ll n;
        cin >> n;
		vector<int> a(n + 1), b(n + 1), tm(n + 1);
		for (int i = 1; i <= n; i++) {
            cin >> a[i] >> b[i];
		}
		for (int i = 1; i <= n; i++) {
            cin >> tm[i];
		}
		ll time = 0;
		for (int i = 0; i < n; i++) {
			ll t1 = (b[i] - a[i] + 1) / 2;
			ll t2 = b[i] - time;
			time += max({t1, t2, 0ll});
			time += a[i + 1] - b[i] + tm[i + 1];
		}
        cout << time << "\n";
	}
	return 0;
}
