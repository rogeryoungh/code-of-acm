#include "basic/index.hpp"

#include "math-P/qpow.hpp"

// @description 预处理逆元、阶乘、阶乘逆元

V<int> iv, fac, ifac;

void pre_all(int u) {
	int l = iv.size(), n = l * 2;
	if (u < l)
		return;
	iv = fac = ifac = V<int>(n + 1, 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	ifac[n] = qpow(fac[n]), iv[n] = qpow(n);
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
		iv[i] = 1ll * ifac[i] * fac[i - 1] % P;
	}
	pre_all(u);
}

// @description 组合数

int C(int n, int m) {
	return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;
}
