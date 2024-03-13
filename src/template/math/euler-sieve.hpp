#pragma once
#include "../base.hpp"

// #region snippet
std::vector<bool> isp;
std::vector<int> primes;
void euler(int n) {
	isp.resize(n + 1, true);
	for (int i = 2; i <= n; i++) {
		if (isp[i])
			primes.push_back(i);
		for (int pj : primes) {
			if (pj > n / i)
				break;
			isp[i * pj] = false;
			if (i % pj == 0)
				break;
		}
	}
}
// #endregion snippet
