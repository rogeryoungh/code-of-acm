Poly bm(const Poly &a) {
	Poly p = {1}, q = {1};
	int l = 0;
	for (int r = 1; r <= a.deg(); r++) {
		int delta = 0;
		for (int j = 0; j <= l; j++) {
			delta = (delta + 1ll * a[r - 1 - j] * p[j]) % P;
		}
		q.insert(q.begin(), 0);
		if (delta == 0)
			continue;
		Poly t = p;
		if (q.deg() > t.deg()) {
			t.redeg(q.deg());
		}
		for (int i = 0; i < q.deg(); i++) {
			t[i] = mo((t[i] - 1ll * delta * q[i]) % P + P);
		}
		if (2 * l <= r - 1) {
			q = p;
			int od = qpow(delta);
			for (int &x : q) {
				x = 1ll * x * od % P;
			}
			l = r - l;
		}
		swap(p, t);
	}
	assert(p.deg() == l + 1);
	return Poly{1} - p;
}

// [x^n] F/G
int divAt(Poly F, Poly G, ll n) {
	int len = std::max(F.deg(), G.deg()), m = get_lim(len);
	for (; n; n >>= 1) {
		F.ntt(m * 2), G.ntt(m * 2);
		for (int i = 0; i < m * 2; i++)
			F[i] = 1ll * F[i] * G[i ^ 1] % P;
		for (int i = 0; i < m; i++)
			G[i] = 1ll * G[i * 2] * G[i * 2 + 1] % P;
		G.redeg(m);
		F.intt(m * 2), G.intt(m);
		for (int i = 0, j = n & 1; i < len; i++, j += 2)
			F[i] = F[j];
		F.redeg(len), G.redeg(len);
	}
	return F[0];
}

int getAn(Poly F, const Poly &A, ll n) {
	F = Poly{1} - F;
	Poly f = (A * F).cut(A.deg());
	return divAt(f, F, n);
}
