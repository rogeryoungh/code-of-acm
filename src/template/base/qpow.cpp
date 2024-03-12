int qpow(int a, i64 n, int m) {
	int ret = 1 % m;
	for (; n > 0; n /= 2) {
		if (n & 1)
			ret = i64(a) * ret % m;
		a = i64(a) * a % m;
	}
	return ret;
}
