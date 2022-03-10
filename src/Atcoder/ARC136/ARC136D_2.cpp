#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int M = 1E6;

bool check(int x) {
	while (x) {
		if (x % 10 >= 5)
			return false;
		x /= 10;
	}
	return true;
}

int main() {
	int N;
	cin >> N;
	vector<int> a(N), dp(M);
	for (int i = 0; i < N; i++) {
		cin >> a[i];
		dp[a[i]]++;
	}

	for (int k = 1; k < M; k *= 10) {
		for (int i = 0; i < M; i += k * 10) {
			for (int j = 0; j < k * 9; j++) {
				dp[i + j + k] += dp[i + j];
			}
		}
	}

	ll ans = 0;
	for (int i = 0; i < N; i++) {
		ans += dp[M - 1 - a[i]] - check(a[i]);
	}
	cout << ans / 2;

	return 0;
}
