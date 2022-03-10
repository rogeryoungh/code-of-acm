#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n, x;
		cin >> n >> x;
		vector<int> a(n);
		for (auto &ai : a)
			cin >> ai;
		vector<int> dp(n + 1, -1E9);
		dp[0] = 0;
		for (int i = 0; i < n; i++) {
			int sum = 0;
			for (int j = i; j < n; j++) {
				sum += a[j];
				dp[j - i + 1] = max(sum, dp[j - i + 1]);
			}
		}
		for (int k = 0; k <= n; k++) {
			int ans = 0;
			for (int i = 0; i <= n; i++)
				ans = max(ans, dp[i] + min(i, k) * x);
			cout << ans << " \n"[k == n];
		}
	}
	return 0;
}
