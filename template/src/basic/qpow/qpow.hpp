#include "basic/index.hpp"

// @description 快速幂(i32)

int qpow(int a, ll b, int m) {
	int ret = 1 % m;
	for (; b > 0; b /= 2) {
		if (b % 2 == 1)
			ret = ll(a) * ret % m;
		a = ll(a) * a % m;
	}
	return ret;
}
