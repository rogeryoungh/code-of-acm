#include "basic/index.hpp"

// @description 线性筛(LPF)

V<int> lpf, primes;
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
