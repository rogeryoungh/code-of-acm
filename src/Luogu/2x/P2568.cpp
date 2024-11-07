// Author: Roger Young
// Date: 2022-02-05 15:19:02.377510

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
	ll s = 0, w = false, c = getchar();
	for (; !isdigit(c); c = getchar())
		w = w || c == '-';
	for (; isdigit(c); c = getchar())
		s = s * 10 + c - '0';
	return w ? -s : s;
}

// END OF HEADER

vector<bool> not_p;
vector<int> primes, phi, mu;
void Euler(int n) {
	not_p.resize(n + 1);
	//    phi.resize(n + 1);
	mu.resize(n + 1);
	//    mu[1] = phi[1] = 1;
	mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!not_p[i]) {
			primes.push_back(i);
			//            phi[i] = i - 1;
			mu[i] = -1;
		}
		for (auto pj : primes) {
			if (pj > n / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0) {
				//                phi[i * pj] = phi[i] * pj;
				mu[i * pj] = 0;
				break;
			}
			//            phi[i * pj] = phi[i] * (pj - 1);
			mu[i * pj] = -mu[i];
		}
	}
}

int main() {
	int n = rr();
	Euler(n);
	vector<ll> sum(n + 1), dp(n + 1);
	for (int i = 1; i <= n; i++) {
		for (auto pj : primes) {
			if (pj > n / i)
				break;
			dp[i * pj] += mu[i];
		}
	}
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + dp[i];

	auto calc = [&](int a, int b) {
		ll ans = 0;
		for (ll l = 1, r; l <= min(a, b); l = r + 1) {
			r = min(a / (a / l), b / (b / l));
			ans += (sum[r] - sum[l - 1]) * (a / l) * (b / l);
		}
		return ans;
	};
	printf("%lld\n", calc(n, n));
	return 0;
}
