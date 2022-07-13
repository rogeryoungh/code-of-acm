#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int N = 1E5 + 5;
ll dp[N][3];

int main() {
	int n;
	cin >> n;
	vector<ll> x(n + 2), h(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> h[i];
	}
	x[0] = -1E15;
	x[n + 1] = 1E15;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
		if (x[i] - h[i] > x[i - 1] + h[i - 1]) { // i 左倒，i+1 右倒
			dp[i][1] = dp[i][0] + 1;
		} else if (x[i] - h[i] > x[i - 1]) { // i 左倒，i+1 不右倒
			dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + 1;
		}
		if (x[i] + h[i] < x[i + 1]) { // i 右倒
			dp[i][2] = dp[i][0] + 1;
		}
	}
	cout << max({dp[n][0], dp[n][1], dp[n][2]});
	return 0;
}
