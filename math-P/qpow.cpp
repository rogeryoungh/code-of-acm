const int P = 998244353;

// @description 快速幂(i32, P)

int qpow(int a, int b = P - 2, int m = P) {
	int ret = m != 1;
	for (; b > 0; b /= 2) {
		if (b % 2 == 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}
