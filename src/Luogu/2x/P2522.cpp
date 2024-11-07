// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-13 17:11:19.534415

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

#include <vector>

const ll N = 50000;

vector<char> notp;
vector<int> prime, mu, phi;
void sieve(int n) {
	notp.resize(n + 1), mu.resize(n + 1);
	//  phi.resize(n + 1);
	mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!notp[i]) {
			prime.push_back(i);
			// phi[i] = i - 1;
			mu[i] = -1;
		}
		int t = n / i;
		for (auto pj : prime) {
			int ti = i * pj;
			if (pj > t)
				break;
			notp[ti] = true;
			if (i % pj == 0) {
				// phi[ti] = phi[i] * pj;
				// mu[ti] = 0;
				break;
			}
			// phi[ti] = phi[i] * (pj - 1);
			mu[ti] = -mu[i];
		}
		mu[i] += mu[i - 1];
	}
}
ll f(ll a, ll b) {
	ll mab = min(a, b);
	ll sum = 0;
	for (ll l = 1, r; l <= mab; l = r + 1) {
		r = min(a / (a / l), b / (b / l));
		// printf("r %lld\n", r);
		sum += (mu[r] - mu[l - 1]) * (a / l) * (b / l);
	}
	return sum;
}

int main() {
	ll T = rr();
	sieve(N - 5);
	// for (int i = 1; i <= N - 5; i++)
	//     mu[i] += mu[i - 1];
	while (T--) {
		ll a = rr(), b = rr(), c = rr(), d = rr();
		ll k = rr();
		a--, c--;
		a /= k, b /= k, c /= k, d /= k;
		ll ans = f(b, d) - f(a, d) - f(b, c) + f(a, c);
		printf("%lld\n", ans);
	}
	return 0;
}
