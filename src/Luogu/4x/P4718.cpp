#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

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
	if (n % 2 == 0)
		return false;
	ll a = n - 1;
	while (a % 2 == 0)
		a /= 2;
	for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
		if (n <= p)
			return true;
		ll t = a, v = qpow128(p, t, n);
		while (t != n - 1 && v != 1 && v != n - 1) {
			v = i128(v) * v % n, t *= 2;
		}
		if (v != n - 1 && t % 2 == 0)
			return false;
	}
	return true;
}

ll pollard_rho(ll N) {
	if (N % 2 == 0)
		return 2;
	if (miller_rabbin(N))
		return N;
	while (true) {
		auto f = [N, c = rand() % (N - 1) + 1](ll x) {
			return (i128(x) * x + c) % N;
		};
		ll x = 0, y = 0, p = 1, q = 1;
		do {
			int w = 128;
			do {
				p = q, x = f(x), y = f(f(y));
				q = i128(p) * abs(x - y) % N;
			} while (w-- && q != 0);
			ll d = std::__gcd(p, N);
			if (d > 1 && d != N)
				return d;
		} while (x != y);
	}
}

auto factor(ll x) {
	vector<ll> v;
	std::function<void(ll)> dfs = [&](ll u) {
		ll fac = pollard_rho(u);
		if (fac == u)
			v.push_back(u);
		else
			dfs(fac), dfs(u / fac);
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
