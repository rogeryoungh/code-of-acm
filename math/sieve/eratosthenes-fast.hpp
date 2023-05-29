#include "basic/index.hpp"

// @description 埃氏筛(卡常)

std::vector<bool> isp;
std::vector<int> primes; // 个数不精确！
void Eratosthenes(int n) {
	isp.resize(n + 6, true);
	auto f = [&](int i) {
		if (isp[i]) {
			primes.push_back(i);
			for (ll j = ll(i) * i; j <= n; j += i)
				isp[j] = false;
		}
	};
	f(2), f(3);
	for (int i = 5; i <= n; i += 6) {
		f(i), f(i + 2);
	}
}
