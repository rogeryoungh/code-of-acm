#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

using i128 = __int128_t;

ll qpow128(ll a, ll b, ll m) {
	ll ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = (i128)ret * a % m;
		a = (i128)a * a % m;
	}
	return ret;
}

bool miller_rabbin(ll n) {
	if (n <= 3)
		return n >= 2;
	ll a = n - 1, b = 0;
	while (1 - (a & 1))
		a >>= 1, ++b;
	for (auto p : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
		if (n == p)
			return true;
		ll v = qpow128(p, a, n);
		if (v == 1 || v == n - 1)
			continue;
		for (int j = 0; j < b && v != 1; j++) {
			ll w = (i128)v * v % n;
			if (v != n - 1 && w == 1)
				return false;
			v = w;
		}
		if (v != 1)
			return false;
	}
	return true;
}

ll pr_rnd(ll r) {
	static std::mt19937 eng(19260817);
	return std::uniform_int_distribution<ll>(0, r)(eng);
}

ll pollard_rho(ll N) {
	if (N % 2 == 0)
		return 2;
	if (miller_rabbin(N))
		return N;
	while (true) {
		ll c = pr_rnd(N - 1) + 1;
		auto f = [&](ll x) {
			return ((i128)x * x + c) % N;
		};
		ll t = 0, r = 0, p = 1, q;
		do {
			for (int i = 0; i < 128; ++i) {
				t = f(t), r = f(f(r));
				if (t == r)
					break;
				if ((q = (i128)p * abs(t - r) % N) == 0)
					break;
				p = q;
			}
			ll d = std::__gcd(p, N);
			if (d > 1 && d != N)
				return d;
		} while (t != r);
	}
}

vector<ll> factor(ll x) {
	vector<ll> v;
	std::function<void(ll)> dfs = [&](ll x) {
		ll fac = pollard_rho(x);
		if (fac == x)
			v.push_back(x);
		else
			dfs(fac), dfs(x / fac);
	};
	dfs(x);
	sort(v.begin(), v.end());
	return v;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		ll x;
		cin >> x;
		auto fac = factor(x);
		ll ret = fac.back();
		if (ret == x) {
			cout << "Prime\n";
		} else {
			cout << ret << "\n";
		}
	}
	return 0;
}
