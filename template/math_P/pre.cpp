vector<int> Inv{1, 1}, fac{1}, ifac{1};

void pre_inv(int n) {
	Inv.resize(n + 1);
	for (int i = 2; i <= n; i++) {
		Inv[i] = 1ll * Inv[P % i] * (P - P / i) % P;
	}
}

void pre_fac(int n) {
	fac.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
}

void pre_ifac(int n) {
	ifac.resize(n + 1);
	ifac[n] = qpow(fac[n]);
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
	}
}
