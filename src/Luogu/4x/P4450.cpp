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
	int a, b, d;
	cin >> a >> b >> d;
	int n = min(a / d, b / d);
	Euler(n + 1);
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += 1ll * mu[i] * (a / d / i) * (b / d / i);
	}
	cout << ans;
	return 0;
}
