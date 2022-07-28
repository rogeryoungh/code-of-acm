#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

#define dbg(x) #x << " = " << (x) << ", "
#define in(x) x = (cin >> x, x)

// END OF HEADER | Author: Roger Young

int main() {
	int in(T);
	while (T--) {
		ll in(n), in(m), in(k);
		ll s1 = 0, s2 = 0;
		vector<int> v(k);
		for (auto &vi : v) {
			cin >> vi;
		}
		sort(v.begin(), v.end());
		for (int i = 0; i < k; i++) {
			ll x = v[i];
			ll u1 = x / n, u2 = x / m;
			if (u1 >= 2) {
				if (s1 + u1 < m) {
					if (m - 2 - s1 >= 2) {
						s1 = min(s1 + u1, m - 2);
					}
				} else {
					s1 += u1;
				}
			}
			if (u2 >= 2) {
				if (s2 + u2 < n) {
					if (n - 2 - s2 >= 2) {
						s2 = min(s2 + u2, n - 2);
					}
				} else {
					s2 += u2;
				}
			}
		}
		bool a = s1 >= m || s2 >= n;
		cout << (a ? "Yes" : "No") << endl;
	}
	return 0;
}
