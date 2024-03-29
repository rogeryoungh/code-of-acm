#include "basic/index.hpp"

std::vector<bool> isp;
std::vector<int> primes, phi, mu;
std::vector<ll> smu;
void Euler(int n) {
	isp.resize(n, true);
	phi = mu = std::vector<int>(n);
	mu[1] = phi[1] = 1;
	for (int i = 2; i < n; i++) {
		if (isp[i]) {
			primes.push_back(i);
			phi[i] = i - 1, mu[i] = -1;
		}
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			isp[i * pj] = false;
			if (i % pj == 0) {
				phi[i * pj] = phi[i] * pj;
				mu[i * pj] = 0;
				break;
			}
			phi[i * pj] = phi[i] * (pj - 1);
			mu[i * pj] = -mu[i];
		}
	}
	smu = std::vector<ll>(n);
	smu[1] = 1;
	for (int i = 2; i < n; i++) {
		smu[i] = smu[i - 1] + mu[i];
	}
}

struct SumMuPhi {
	ll n;
	std::vector<ll> sum;
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
