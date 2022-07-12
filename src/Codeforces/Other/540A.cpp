#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int n;
	string a, b;
	cin >> n >> a >> b;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int diff = std::abs(a[i] - b[i]);
		ans += std::min(diff, 10 - diff);
	}
	cout << ans;
	return 0;
}
