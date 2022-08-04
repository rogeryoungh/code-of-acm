#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
using ll = int64_t;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int P = 666623333;

vector<bool> not_p;
vector<int> primes, phi, mu, smu;
void Euler(int n) {
	not_p.resize(n);
	smu = phi = mu = vector<int>(n);
	smu[1] = mu[1] = phi[1] = 1;
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
	for (int i = 2; i < n; i++) {
		smu[i] = smu[i - 1] + mu[i];
	}
}

using i128 = __int128_t;

struct SumMuPhi {
	ll n;
	vector<ll> sum;
	SumMuPhi(ll u) : n(u), sum(u / smu.size() + 1) {}
	ll Smu(ll u) {
		if (u < smu.size()) {
			return smu[u];
		}
		if (sum[n / u] != 0) {
			return sum[n / u];
		}
		ll ret = 1;
		for (ll l = 2, r; l <= u; l = r + 1) {
			r = u / (u / l);
			ret -= (r - l + 1) * Smu(u / l);
		}
		return sum[n / u] = ret;
	}
	ll Sphi(ll u) {
		i128 ret = 0;
		for (ll l = 1, r; l <= u; l = r + 1) {
			r = u / (u / l);
			ll t = Smu(r) - Smu(l - 1);
			ret += i128(t) * (u / l) * (u / l);
		}
		return (ret + 1) / 2 % P;
	}
};

int main() {
	ll l, r;
	cin >> l >> r;
	Euler(pow(r + 10, 0.66));

	ll ans = i128(l + r) * (r - l + 1) / 2 % P;
	ans -= SumMuPhi(r).Sphi(r) - SumMuPhi(l - 1).Sphi(l - 1);

	cout << (ans + P) % P;
	return 0;
}
