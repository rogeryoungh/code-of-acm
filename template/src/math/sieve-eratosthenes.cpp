#include "basic/index.hpp"

// @description 埃氏筛

vector<bool> not_p;
vector<int> primes;
void Eratosthenes(int n) {
	not_p.resize(n);
	for (int i = 2; i < n; i++) {
		if (not not_p[i]) {
			primes.push_back(i);
			for (int j = i; j <= (n - 1) / i; j++)
				not_p[i * j] = true;
		}
	}
}
