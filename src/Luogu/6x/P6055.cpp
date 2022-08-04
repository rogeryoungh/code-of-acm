#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
using ll = int64_t;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int P = 998244353;

vector<bool> not_p;
vector<int> primes, phi, mu;
void Euler(int n) {
	not_p.resize(n);
	phi = mu = vector<int>(n);
	mu[1] = phi[1] = 1;
	for (int i = 2; i < n; i++) {
		if (!not_p[i]) {
			primes.push_back(i);
			phi[i] = i - 1, mu[i] = -1;
		}
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0) {
				phi[i * pj] = phi[i] * pj;
				mu[i * pj] = 0;
				break;
			}
			phi[i * pj] = phi[i] * (pj - 1);
			mu[i * pj] = -mu[i];
		}
	}
}

struct SumMu {
	int n, m;
	vector<int> sum;
	unordered_map<int, int> mp;
	SumMu(int n) : sum(n) {
		for (int i = 1; i < n; i++) {
			sum[i] = sum[i - 1] + mu[i];
		}
	}
	int S(int n) {
		if (n < sum.size()) {
			return sum[n];
		}
		if (mp.count(n)) {
			return mp[n];
		}
		int ret = 1;
		for (ll l = 2, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ret -= (r - l + 1) * S(n / l);
		}
		return mp[n] = ret;
	}
};

int main() {
	ll n;
	cin >> n;
	Euler(1E6);
	SumMu smu(1E6);

	ll ans = 0;
	for (ll l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		int s = (smu.S(r) - smu.S(l - 1) + P) % P;
		ll t = n / l;
		ans += s * t % P * t % P * t % P;
	}
	cout << ans % P;

	return 0;
}
