#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int phi(int x) {
	int ans = 0;
	for (int i = 1; i <= x; i++) {
		ans += std::__gcd(i, x) == 1;
	}
	return ans;
}

int d(int x) {
	int ans = 0;
	for (int i = 1; i <= x; i++) {
		ans += (x % i == 0);
	}
	return ans;
}

int main() {
	const int N = 100;
	vector<int> E(N), F(N);
	vector<ll> SE(N), SF(N);
	for (int i = 1; i < N; i++) {
		E[i] = phi(i);
		F[i] = d(i);
		SE[i] = SE[i - 1] + E[i];
		SF[i] = SF[i - 1] + F[i];
	};
	auto solve = [&](int n) {
		int ans = 0;
		n = min(30, n);
		for (int i = 0; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (SE[j] - SE[i] == SF[j] - SF[i]) {
					ans++;
				}
			}
		}
		return ans;
	};

	int T;
	cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		int x;
		cin >> x;
		cout << "Case " << tt << ": " << solve(x) << endl;
	}
	return 0;
}
