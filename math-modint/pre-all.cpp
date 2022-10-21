#include "basic/index.hpp"

#include "math-modint/basic.cpp"

// @description 预处理逆元、阶乘、阶乘逆元

std::vector<Z> iv, fac, ifac;

void pre_all(int n) {
	n = std::max(5, n);
	iv = fac = ifac = std::vector<Z>(n + 1);
	iv[0] = iv[1] = fac[0] = ifac[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i;
	}
	ifac[n] = fac[n].inv(), iv[n] = Z(n).inv();
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1);
		iv[i] = ifac[i] * fac[i - 1];
	}
}

// @description 组合数

Z C(int n, int m) {
	return fac[n] * ifac[m] * ifac[n - m];
}
