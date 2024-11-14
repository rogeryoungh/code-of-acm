#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

std::vector<int> lpf, primes;
void Euler(int n) {
	lpf.resize(n + 1);
	for (int i = 2; i <= n; i++) {
		if (!lpf[i])
			lpf[i] = i, primes.push_back(i);
		for (auto pj : primes) {
			if (pj > n / i)
				break;
			lpf[i * pj] = pj;
			if (i % pj == 0)
				break;
		}
	}
}

int32_t main() {
	Euler(4E5 + 10);
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::vector<int> a(n);
		int ans = -1, cnt = 0;
		for (int &i : a) {
			std::cin >> i;
			if (lpf[i] == i) {
				ans = i, cnt += 1;
			}
		}
		if (cnt == 0) {
			ans = 2;
		}
		bool flag = cnt < 2;
		for (int i : a) {
			if (i % ans != 0) {
				int x = -1;
				if (ans <= lpf[i]) {
					x = ans * 2;
				} else {
					x = 2 * (ans + lpf[i] - ans % lpf[i]);
					std::vector<int> fac;
					int ti = i;
					while (ti > 1) {
						fac.push_back(lpf[ti]);
						ti /= lpf[ti];
					}
					for (int f : fac) {
						x = std::min(x, 2 * (ans + f - ans % f));
					}
				}
				flag = flag && i >= x;
			}
		}
		// std::cout << ans << std::endl;
		std::cout << (flag ? ans : -1) << '\n';
	}
	return 0;
}
