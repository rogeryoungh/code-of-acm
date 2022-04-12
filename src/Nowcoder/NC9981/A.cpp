#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int P = 1E9 + 7;

int qpow(int a, int b = P - 2, int m = P) {
	int ret = P != 1;
	for (; b > 0; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % P;
		a = 1ll * a * a % P;
	}
	return ret;
}

int main() {
	ll n;
	cin >> n;
	ll ans = 576ll * qpow(26, n + 1) % P - (599 + 24 * n) * qpow(25, n + 1) % P;
	cout << (ans + P * 2 - 1) * qpow(14400) % P;
	return 0;
}
