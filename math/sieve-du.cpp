#include <cstdint>
#include <vector>
using namespace std;
using ll = int64_t;

vector<bool> not_p;
vector<int> primes, phi, mu;
vector<ll> smu;
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
	smu = vector<ll>(n);
	smu[1] = 1;
	for (int i = 2; i < n; i++) {
		smu[i] = smu[i - 1] + mu[i];
	}
}

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
		ll ret = 0;
		for (ll l = 1, r; l <= u; l = r + 1) {
			r = u / (u / l);
			ret += (Smu(r) - Smu(l - 1)) * (u / l) * (u / l);
		}
		return (ret + 1) / 2;
	}
};
