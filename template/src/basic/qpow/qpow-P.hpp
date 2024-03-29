#include "basic/index.hpp"

const int P = 998244353;

// @description 快速幂(i32, P)

int qpow(int a, ll b = P - 2, int m = P) {
	int ret = 1 % m;
	for (; b > 0; b /= 2) {
		if (b % 2 == 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

inline int mo(int x) {
	return x >= P ? x - P : x;
}
