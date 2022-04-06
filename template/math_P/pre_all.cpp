const int P = 998244353;

int qpow(int a, int b = P - 2, int m = P) {
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

vector<int> Inv{1, 1}, fac{1}, ifac{1};

void pre_all(int n) {
	Inv.resize(n + 1), fac.resize(n + 1), ifac.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	ifac[n] = qpow(fac[n]), Inv[n] = qpow(n);
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
		Inv[i] = 1ll * ifac[i] * fac[i - 1] % P;
	}
}