#include <vector>
using ll = long long;
using namespace std;

// @problem https://www.luogu.com.cn/problem/P1495

pair<ll, ll> exgcd(ll a, ll b) {
	if (!b) {
		return {1, 0};
	}
	auto [y, x] = exgcd(b, a % b);
	return {x, y - a / b * x};
}

ll inv_mod(ll a, ll p) {
	return (exgcd(a, p).first % p + p) % p;
}

// @description 中国剩余定理

ll crt(const vector<ll> &aa, const vector<ll> &m) {
	ll prod = 1, ret = 0, n = aa.size();
	for (ll ni : m)
		prod *= ni;
	for (int i = 0; i < n; i++) {
		ll u = prod / m[i], v = inv_mod(u, m[i]);
		ret = (ret + aa[i] * u * v) % prod;
	}
	return ret;
}