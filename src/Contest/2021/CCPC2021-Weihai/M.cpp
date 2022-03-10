// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-27 12:59:02.018008

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')
#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (!isdigit(c))
		w = 1 - 2 * (c == '-'), c = getchar();
	while (isdigit(c))
		s = s * 10 + c - '0', c = getchar();
	return s * w;
}

// END OF HEADER

#define ACM_MOD 998244353
const int P = ACM_MOD;

#ifdef ACM_MOD
int qpow(ll a, ll b, ll m = ACM_MOD) {
#else
int qpow(ll a, ll b, ll m) {
#endif
	ll ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a % m;
		a = a * a % m;
	}
	return ret;
}

#ifdef ACM_MOD
ll inv(ll a, ll m = ACM_MOD) {
#else
ll inv(ll a, ll m) {
#endif
	return qpow(a, m - 2, m);
}

ll mo(ll n) {
	return (n + P) % P;
}

struct Mint {
	int v = 0;
	Mint(int _v = 0) {
		v = _v;
	}
	Mint &operator=(const int &m) {
		v = m;
		return *this;
	}
	Mint &operator+=(const Mint &m) {
		v += m.v;
		v = v < P ? v : v - P;
		return *this;
	}
	Mint &operator-=(const Mint &m) {
		v -= m.v;
		v = v < 0 ? v + P : v;
		return *this;
	}
	Mint operator-() const {
		if (v > 0)
			return P - v;
		return 0;
	}
	Mint &operator*=(const Mint &m) {
		v = ll(v) * m.v % P;
		return *this;
	}
	Mint operator+(const Mint &m) const {
		return Mint(*this) += m;
	}
	Mint operator-(const Mint &m) const {
		return Mint(*this) -= m;
	}
	Mint operator*(const Mint &m) const {
		return Mint(*this) *= m;
	}
};

using Poly = vector<Mint>;
Poly fac, ifac;

void pre_fac(int lim) {
	fac.resize(lim + 1);
	fac[0] = 1;
	for (int i = 1; i <= lim; i++) {
		fac[i] = fac[i - 1] * i;
	}
}

void pre_ifac(int lim) {
	ifac.resize(lim + 1);
	ifac[lim] = inv(fac[lim].v);
	for (int i = lim - 1; i >= 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1);
	}
}

Mint solve(int n, int m, int k) {
	Mint ans = 0;
	for (int i = 0; k * i < m + 1 && i < n - m + 2; i++) {
		auto t1 = ifac[i] * ifac[n - m + 1 - i] * (n - m + 1);
		auto t2 = fac[n - k * i] * ifac[m - k * i];
		ans += t1 * t2 * (i & 1 ? P - 1 : 1);
	}
	return ans;
}

int main() {
	ll n = rr(), m = rr(), k = rr();
	if (n < m || m < k || n < k) {
		printf("0");
	} else if (k == 0) {
		printf("%d", m == 0);
	} else {
		pre_fac(n * 2), pre_ifac(n * 2);
		auto ans = solve(n, m, k + 1) - solve(n, m, k);
		printf("%d", ans.v);
	}
	return 0;
}