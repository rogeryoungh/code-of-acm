#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int n;
	cin >> n;
	vector<int> vis(n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int aij;
			cin >> aij;
			if (aij == 1) {
				vis[i] = true;
			} else if (aij == 2) {
				vis[j] = true;
			} else if (aij == 3) {
				vis[i] = vis[j] = true;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += vis[i];
	}
	cout << n - ans << endl;
	for (int i = 1; i <= n; i++) {
		if (not vis[i]) {
			cout << i << ' ';
		}
	}
	return 0;
}
