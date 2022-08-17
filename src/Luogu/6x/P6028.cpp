#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

int ____ = cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

using f80 = long double;

const f80 g = 0.57721566490153286060651209;

const int N = 1E6;

int main() {
	ll n;
	cin >> n;
	f80 sum = 0;
	vector<f80> v(N);
	for (int i = 1; i < N; i++) {
		v[i] = v[i - 1] + 1.0 / i;
	}
	auto S = [&](ll x) {
		return x >= N ? log(x) + g : v[x];
	};
	for (ll l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		sum += (S(r) - S(l - 1)) * (n / l);
	}
	printf("%.15Lf\n", sum);
	return 0;
}
