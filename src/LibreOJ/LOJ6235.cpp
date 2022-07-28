#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

using Z = ll;

struct Min25 {
	ll n, sn, m = 0;
	vector<int> primes;
	vector<Z> sum;
	Z fp(int p, int k) {
		return k == 1;
	}
	int id(ll x) {
		return x <= sn ? x : m - (n / x) + 1;
	}
	Min25(ll u) : n(u), sn(sqrt(n) + 1), sum(sn * 2 + 5) {
		vector<bool> not_p(sn + 1);
		vector<ll> w(sn * 2 + 5);
		for (ll l = 1, r; l <= n; l = r + 1) {
			w[++m] = r = n / (n / l);
		}
		vector<Z> s0(m + 1);
		for (int i = 1; i <= m; i++) {
			Z r = w[i];
			s0[i] = r - 1;
		}
		primes.push_back(0);
		for (int i = 2; i <= sn; i++) {
			if (not not_p[i]) {
				primes.push_back(i);
				for (int j = i; j <= (sn - 1) / i; j++)
					not_p[i * j] = true;
				for (int j = m; w[j] >= 1ll * i * i; j--) {
					s0[j] -= s0[id(w[j] / i)] - s0[i - 1];
				}
			}
		}
		for (int i = 2; i <= m; i++) {
			sum[i] = s0[i];
		}
		for (int i = 1; i <= n; i++) {
			int uu = id(n / i);
			cerr << dbg(n / i) << dbg(sum[uu]) << endl;
		}
	}
	Z eval() {
		return sum[id(n)];
	}
};

int main() {
	ll n;
	cin >> n;

	cout << Min25(n).eval();

	return 0;
}
