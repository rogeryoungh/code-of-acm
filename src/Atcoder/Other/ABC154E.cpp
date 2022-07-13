#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int N = 100 + 5;

ll dp[N][5];

void init() {
	dp[0][0] = 1;
	for (int i = 1; i <= 105; i++) {
		dp[i][0] = dp[i - 1][0];
		for (int j = 1; j <= 3; j++) {
			dp[i][j] = dp[i - 1][j] + 9 * dp[i - 1][j - 1];//

			cerr << i << " " << j << " = " << dp[i][j] << endl;
            cerr << pow(9, j) * i << endl;
		}
	}
}

auto s2v(const string &s) {
	vector<int> v;
	for (auto si : s) {
		v.push_back(si - '0');
	}
	return v;
}

ll solve(const string &s, int k) {
	int len = s.size();
	vector<int> v = s2v(s);
	ll ans = 0, now = 0;
	for (int i = 0; i < len; i++) {
		if (v[i]) {
			if (k - now >= 0)
				ans += dp[len - i - 1][k - now];
			if (k - now - 1 >= 0)
				ans += (v[i] - 1) * dp[len - i - 1][k - now - 1];
			now++;
		}
		if (i == len - 1) {
			ans += (now == k);
		}
	}
	return ans;
}

int main() {
	init();
	int k;
	string s;
	cin >> s >> k;
	cout << solve(s, k);
	return 0;
}
