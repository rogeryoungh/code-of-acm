#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int P = 1E9 + 7;

vector<bool> not_p;
vector<int> primes; // 注意，个数可能不精确！
void Euler(int n) {
	not_p.resize(n + 1);
	auto _ = [&](int i) {
		if (!not_p[i])
			primes.push_back(i);
		for (auto pj : primes) {
			if (pj > n / i)
				break;
			not_p[i * pj] = true;
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
	ll n;
	cin >> n;
	if (n <= 5) {
		cout << "empty";
		return 0;
	}
	Euler(n / 2);
	ll ans = 1;
	for (auto pj : primes) {
		ll tn = n;
		if (pj == 2) {
			tn /= 3;
		} else {
			tn /= 2;
		}
		tn /= pj;
		while (tn > 0) {
			tn /= pj;
			ans = ans * pj % P;
		}
	}
	cout << ans;
	return 0;
}
