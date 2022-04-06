#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int P = 998244353;

int qpow(int a, int b = P - 2, int m = P) {
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

vector<int> Inv{1, 1}, fac{1}, ifac{1};

inline int mo(int u) {
	return u >= P ? u - P : u;
}

void pre_all(int n) {
	Inv.resize(n + 1), fac.resize(n + 1), ifac.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	ifac[n] = qpow(fac[n]), Inv[n] = qpow(n);
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
		Inv[i] = 1ll * ifac[i] * fac[i - 1] % P;
	}
}

const int N = 60;

int dp[N][N][N];

int main() {
	pre_all(N * 10);

	int n, m, k;
	cin >> n >> m >> k;
	vector<int> p(n);
	int tsum = 0;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		tsum = (tsum + p[i]) % P;
	}
	int iv_sum = qpow(tsum);
	vector<int> pw[N];
	for (int i = 0; i < n; i++) {
		p[i] = 1ll * p[i] * iv_sum % P;

		pw[i].resize(N);
		pw[i][0] = 1;
		int pi = p[i];
		for (int j = 1; j < N; j++) {
			pw[i][j] = 1ll * pi * ifac[j] % P;
			pi = 1ll * pi * p[i] % P;
		}
	}

	dp[0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < n; j++) {
			for (int x = 0; x <= k; x++) {
				dp[i][j][x] = mo(dp[i][j][x] + dp[i - 1][j][x]);
				for (int y = 1; y <= k - x; y++) {
					ll mul = 1ll * dp[i - 1][j][x] * pw[i - 1][y];
					dp[i][j + 1][x + y] = (dp[i][j + 1][x + y] + mul) % P;
				}
			}
		}
	}

	cout << 1ll * dp[n][m][k] * fac[k] % P;

	return 0;
}
