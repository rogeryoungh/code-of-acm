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

vector<int> iv{1, 1}, fac{1}, ifac{1};

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
