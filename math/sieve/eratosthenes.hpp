#include "basic/index.hpp"

// @description 埃氏筛

std::vector<bool> isp;
std::vector<int> primes;
void Eratosthenes(int n) {
	isp.resize(n + 1, true);
	for (int i = 2; i <= n; i++) {
		if (isp[i]) {
			primes.push_back(i);
			for (ll j = ll(i) * i; j <= n; j += i)
				isp[j] = false;
		}
	}
}
