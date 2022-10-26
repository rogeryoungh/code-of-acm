#include "basic/index.hpp"

// @description 埃氏筛(卡常)

std::vector<bool> not_p;
std::vector<int> primes; // 个数不精确！
void Eratosthenes(int n) {
	not_p.resize(n + 6);
	auto f = [&](int i) {
		if (not not_p[i]) {
			primes.push_back(i);
			for (int j = i; j <= (n - 1) / i; j++)
				not_p[i * j] = true;
		}
	};
	f(2), f(3);
	for (int i = 5; i < n; i += 6) {
		f(i), f(i + 2);
	}
}
