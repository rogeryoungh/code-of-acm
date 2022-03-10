#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

vector<bool> notp;
vector<int> primes;
void Euler(int n) {
	notp.resize(n + 1);
	auto _ = [&](int i) {
		if (!notp[i])
			primes.push_back(i);
		int t = n / i;
		for (auto pj : primes) {
			if (pj > t)
				break;
			notp[i * pj] = true;
			if (i % pj == 0)
				break;
		}
	};
	_(2), _(3), _(5);
	for (int i = 1; i <= n / 6; i++) {
		_(i * 6 + 1), _(i * 6 + 5);
	}
}

int main() {
	int n, q;
	cin >> n >> q;
	Euler(n);
	while (q--) {
		int k;
		cin >> k;
		printf("%d\n", primes[k - 1]);
	}
	return 0;
}
