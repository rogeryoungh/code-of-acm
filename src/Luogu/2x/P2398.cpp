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
	int n;
	cin >> n;
	Euler(n + 1);
	ll ans = 0;
	vector<ll> sphi(n + 1);
	for (int i = 1; i <= n; i++) {
		sphi[i] = sphi[i - 1] + phi[i];
	}
	for (int i = 1; i <= n; i++) {
		ans += i * (2 * sphi[n / i] - 1);
	}
	cout << ans;
	return 0;
}
