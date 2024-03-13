#pragma once
#include "../base.hpp"

// #region snippet
std::vector<bool> isp;
std::vector<int> primes;
void Eratosthenes(int n) {
	isp.resize(n + 1, true);
	for (int i = 2; i <= n; i++) {
		if (isp[i]) {
			primes.push_back(i);
			for (i64 j = i64(i) * i; j <= n; j += i)
				isp[j] = false;
		}
	}
}
// #endregion snippet
