struct Poly : vector<int> {
	using vector::vector;
	static Poly &mul(Poly &f, Poly &g, int n);
};
Poly w{1, 1};
inline int get_lim(int m) {
	return 1 << std::__lg(m * 2 - 1);
}
inline int mo(int u) {
	return u >= P ? u - P : u;
}
void pre_w(int n) {
	int l = w.size(), l2 = l * 2;
	if (n <= l)
		return;
	w.resize(l2);
	int p = qpow(3, (P - 1) / l2);
	for (int i = l; i < l2; i += 2) {
		w[i] = w[i / 2];
		w[i + 1] = 1ll * w[i] * p % P;
	}
	pre_w(n);
}

static int ntt_size = 0;

void ntt(auto f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = n / 2; l; l /= 2)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				int x = f[i + j], y = f[i + j + l];
				f[i + j + l] = 1ll * (x - y + P) * w[j + l] % P;
				f[i + j] = mo(x + y);
			}
}

void intt(auto f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = 1; l < n; l *= 2)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				int x = f[i + j];
				int y = 1ll * w[j + l] * f[i + j + l] % P;
				f[i + j] = mo(x + y), f[i + j + l] = mo(x - y + P);
			}
	const int ivn = P - (P - 1) / n;
	for (int i = 0; i < n; i++)
		f[i] = 1ll * f[i] * ivn % P;
	reverse(f + 1, f + n);
}

Poly &Poly::mul(Poly &f, Poly &g, int n) {
	f.resize(n), g.resize(n);
	ntt(f.begin(), n), ntt(g.begin(), n);
	for (int i = 0; i < n; i++)
		f[i] = 1ll * f[i] * g[i] % P;
	return intt(f.begin(), n), f;
}

Poly operator*(Poly f, Poly g) {
	int m = f.size() + g.size() - 1;
	Poly::mul(f, g, get_lim(m));
	return f.resize(m), f;
}
