#include "basic/index.hpp"

// @description 埃氏筛

V<bool> isp;
V<int> primes;
void Eratosthenes(int n) {
	isp.resize(n, true);
	for (int i = 2; i < n; i++) {
		if (isp[i]) {
			primes.push_back(i);
			for (ll j = ll(i) * i; j < n; j += i)
				isp[j] = false;
		}
	}
}
