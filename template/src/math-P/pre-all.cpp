#include <vector>
using namespace std;

const int P = 998244353;

// @description 快速幂(i32, P)

int qpow(int a, int b = P - 2, int m = P) {
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

// @description 预处理逆元、阶乘、阶乘逆元

vector<int> iv{1, 1}, fac{1}, ifac{1};

void pre_all(int n) {
	iv.resize(n + 1), fac.resize(n + 1), ifac.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	ifac[n] = qpow(fac[n]), iv[n] = qpow(n);
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
		iv[i] = 1ll * ifac[i] * fac[i - 1] % P;
	}
}

// @description 组合数

int C(int n, int m) {
	return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;
}
