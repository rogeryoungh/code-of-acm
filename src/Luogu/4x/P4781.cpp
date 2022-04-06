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

ll lagrange(const vector<ll> &x, const vector<ll> &y, ll k) {
    ll sum = 0, n = x.size();
    for (int i = 0; i < n; i++) {
        int s1 = 1, s2 = 1;
        for (int j = 0; j < n; j++) {
            if (j == i)
                continue;
            s1 = 1ll * s1 * (k - x[j] + P) % P;
            s2 = 1ll * s2 * (x[i] - x[j] + P) % P;
        }
        sum += 1ll * s1 * qpow(s2) % P * y[i] % P;
    }
    return sum % P;
}

int main() {
    ll n, k;
    cin >> n >> k;
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    cout << lagrange(x, y, k);
	return 0;
}
