#include "basic/index.hpp"

// @description 线性筛

std::vector<bool> isp;
std::vector<int> primes;
void Euler(int n) {
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
