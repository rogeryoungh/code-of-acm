#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int n, k;
	cin >> n >> k;
	if (n < 6 && k == n / 2) {
		cout << -1;
		exit(0);
	}
	vector<int> vis(n + 1), ans;
	for (int i = 2; i <= n; i += 2) {
		if (i == 6)
			continue;
		ans.push_back(i);
	}
	ans.push_back(6);
	ans.push_back(3);
	for (int i = 0; i <= k; i++) {
		cout << ans[i] << " ";
		vis[ans[i]] = true;
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i])
			cout << i << " ";
	}
	return 0;
}
