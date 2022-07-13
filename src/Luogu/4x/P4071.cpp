#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int P = 1E9 + 7;

int qpow(int a, int b = P - 2, int m = P) {
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

vector<int> Inv{1, 1}, fac{1}, ifac{1}, D{1, 0, 1};

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
	D.resize(n + 1);
	for (int i = 3; i <= n; i++) {
		D[i] = 1ll * (i - 1) * (D[i - 1] + D[i - 2]) % P;
	}
}

int choose(int n, int m) {
	return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;
}

int main() {
	pre_all(1E6 + 10);
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;
		int ans = 1ll * choose(n, m) * D[n - m] % P;
		cout << ans << endl;
	}
	return 0;
}
