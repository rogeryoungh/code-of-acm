#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

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

int main() {
	int n, m;
	cin >> n >> m;
	int x = min(n, m);
	Euler(x + 1);

	vector<ll> sphi(x + 1);
	for (int i = 1; i <= x; i++) {
		sphi[i] = sphi[i - 1] + phi[i];
	}

	ll ans = 0;
	for (int l = 1, r; l <= x; l = r + 1) {
		r = min(n / (n / l), m / (m / l));
		ans += 1ll * (sphi[r] - sphi[l - 1]) * (n / l) * (m / l);
	}
	cout << ans * 2 - 1ll * n * m;
	return 0;
}
