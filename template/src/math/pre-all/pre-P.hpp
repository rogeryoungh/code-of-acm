#include "basic/index.hpp"

#include "basic/qpow/qpow-P.hpp"

V<int> iv{1, 1}, fac{1}, ifac{1};

// @description 预处理逆元

void pre_inv(int n) {
	iv.resize(n + 1);
	for (int i = 2; i <= n; i++) {
		iv[i] = 1ll * iv[P % i] * (P - P / i) % P;
	}
}

// @description 预处理阶乘

void pre_fac(int n) {
	fac.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
}

// @description 预处理阶乘逆元

void pre_ifac(int n) {
	ifac.resize(n + 1);
	ifac[n] = qpow(fac[n]);
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
	}
}

// @description 组合数

int C(int n, int m) {
	return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;
}
