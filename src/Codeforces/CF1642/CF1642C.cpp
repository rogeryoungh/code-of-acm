#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		ll x;
		cin >> n >> x;
		vector<ll> a(n);
		for (auto &ai : a)
			cin >> ai;
		sort(a.begin(), a.end());
		vector<int> vis(n);
		int l = 0, r = -1;
		while (r < n - 1) {
			r++;
			while (a[l] * x < a[r] || (a[l] * x == a[r] && vis[l]))
				l++;
			if (a[l] * x == a[r])
				vis[l] = vis[r] = true;
		}

		int ans = 0;
		for (auto vi : vis)
			ans += vi;
		cout << n - ans << "\n";
	}
	return 0;
}
