#include "basic/index.hpp"

// @description 线性筛

vector<bool> not_p;
vector<int> primes;
void Euler(int n) {
	not_p.resize(n);
	for (int i = 2; i < n; i++) {
		if (not not_p[i])
			primes.push_back(i);
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0)
				break;
		}
	}
}
