struct PolyEI {
	int raw_n, n;
	vector<Poly> p;
	PolyEI(Poly a) : raw_n(a.deg()), n(get_lim(raw_n)), p(n * 2) {
		a.redeg(n);
		for (int i = 0; i < n; i++)
			p[i + n] = {1, -a[i]};
		for (int i = n - 1; i; i--) {
			int ls = i * 2, rs = i * 2 + 1;
			int len = get_lim(p[ls].deg());
			p[ls].ntt(len), p[rs].ntt(len), p[i].redeg(len);
			for (int j = 0; j < len; j++)
				p[i][j] = p[ls][j] * p[rs][j];
			p[i].intt(len);
			p[i].push_back(p[i][0] - 1), p[i][0] = 1;
		}
	}
	Poly eval(const Poly &f) { // PolyEI(x).eval(f)
		int m = f.deg();
		if (m == 1)
			return Poly(raw_n, f[0]);
		Poly q = f.rev().div(m, p[1]).redeg(n);
		rotate(q.begin(), q.begin() + m, q.end());
		for (int k = n, o = 1; k > 1; k >>= 1)
			for (int i = 0; i < n; i += k, o++) {
				if (i >= raw_n)
					continue;
				Poly foo(k), bar(k);
				auto qi = q.begin() + i;
				ntt(qi, k);
				for (int j = 0; j < k; j++) {
					foo[j] = qi[j] * p[o * 2 + 1][j];
					bar[j] = qi[j] * p[o * 2][j];
				}
				foo.intt(k), bar.intt(k);
				copy(foo.begin() + k / 2, foo.end(), qi);
				copy(bar.begin() + k / 2, bar.end(), qi + k / 2);
			}
		return q.cut(raw_n);
	}
	Poly inter(const Poly &y) { // PolyEI(x).inter(y)
		Poly q = Poly(p[1]).redeg(raw_n + 1);
		q = eval(q.rev().deriv()).redeg(n);
		for (int i = 0; i < raw_n; i++)
			q[i] = y[i] / q[i];
		for (int k = 1, h = n / 2; k < n; k *= 2, h >>= 1)
			for (int i = 0, o = h; i < n; i += k * 2, o++) {
				if (i >= raw_n)
					continue;
				auto qi = q.begin() + i;
				Poly foo(qi, qi + k), bar(qi + k, qi + k * 2);
				foo.ntt(k * 2), bar.ntt(k * 2);
				for (int j = 0; j < k * 2; j++) {
					qi[j] = foo[j] * p[o * 2 + 1][j] + bar[j] * p[o * 2][j];
				}
				intt(qi, k * 2);
			}
		return q.cut(raw_n).rev();
	}
};
