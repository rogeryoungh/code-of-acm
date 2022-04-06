#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 300 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll G[N][N], f[N][N];
void floyd(int n) {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	memset(G, 0x3f, sizeof(G));
	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i < m; i++) {
		ll ai, bi, ci;
		cin >> ai >> bi >> ci;
		G[ai][bi] = G[bi][ai] = ci;
		f[ai][bi] = f[bi][ai] = ci;
	}
	for (int i = 1; i <= n; i++) {
		f[i][i] = G[i][i] = 0;
	}

	floyd(n);

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (G[i][j] == INF)
				continue;
			bool flag = false;
			for (int k = 1; k <= n; k++) {
				if (i == k || j == k)
					continue;
				if (f[i][k] + f[k][j] <= G[i][j])
					flag = true;
			}
			ans += flag;
		}
	}
	cout << ans;

	return 0;
}
