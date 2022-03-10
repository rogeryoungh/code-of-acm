// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-11 13:47:14.315886

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128_t;
using ull = unsigned long long;
using ld = long double;

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

#define ACM_MOD 1000000007

const int maxn = 1000000 + 10, P = ACM_MOD;

#ifdef ACM_MOD
ll qpow(ll a, ll b, ll m = ACM_MOD) {
#else
ll qpow(ll a, ll b, ll m) {
#endif
	ll ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a % m;
		a = a * a % m;
	}
	return ret;
}

vector<int> aa;
vector<int> tong;

bool notp[maxn];
vector<int> prime;
void Euler(int n) {
	for (int i = 2; i <= n; i++) {
		if (!notp[i]) {
			prime.push_back(i);
		}
		int t = n / i;
		for (auto pj : prime) {
			if (pj > t)
				break;
			notp[i * pj] = true;
			if (i % pj == 0)
				break;
		}
	}
}

int main() {
	int n = rr();
	tong.resize(maxn);
	Euler(maxn - 5);
	for (int i = 0; i < n; i++) {
		ll ai = rr();
		// aa[i] = ai;
		for (auto pi : prime) {
			if (pi > 1001)
				break;
			ll w = 0;
			while (ai % pi == 0) {
				ai /= pi;
				w = 1 - w;
			}
			if (w == 1) {
				tong[pi]++;
			}
		}
		if (ai > 1)
			tong[ai]++;
	}
	ll ans = 1;
	for (auto pi : prime) {
		if (tong[pi] == 0)
			continue;
		ll tans = min(tong[pi], n - tong[pi]);
		ans = ans * qpow(pi, tans) % P;
	}
	printf("%lld\n", ans);

	return 0;
}