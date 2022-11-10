#include "basic/index.hpp"

// @description 线性筛积性函数

V<bool> isp;
V<int> primes, phi, mu;
void Euler(int n) {
	isp.resize(n, true);
	phi = mu = V<int>(n);
	mu[1] = phi[1] = 1;
	for (int i = 2; i < n; i++) {
		if (isp[i]) {
			primes.push_back(i);
			phi[i] = i - 1, mu[i] = -1;
		}
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			isp[i * pj] = false;
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