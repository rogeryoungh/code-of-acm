struct Poly : vector<int> { // 大常数板子
	using vector::vector;
#define T (*this)
	int deg() const {
		return size();
	}
	Poly &redeg(int m) {
		return resize(m), T;
	}
	Poly cut(int m, int l = 0) const {
		return {begin() + l, begin() + min(m + l, deg())};
	}
	friend Poly operator+(const Poly &f, const Poly &g) {
		Poly h = Poly(f).redeg(max(f.deg(), g.deg()));
		for (int i = 0; i < g.deg(); i++)
			h[i] = mo(h[i] + g[i]);
		return h;
	}
	friend Poly operator-(const Poly &f, const Poly &g) {
		Poly h = Poly(f).redeg(max(f.deg(), g.deg()));
		for (int i = 0; i < g.deg(); i++)
			h[i] = mo(h[i] - g[i] + P);
		return h;
	}
	Poly operator*(int k) {
		Poly f = T;
		for (int &fi : f)
			fi = 1ll * fi * k % P;
		return f;
	}
	Poly &ntt(int n) {
		return redeg(n), ::ntt(begin(), n), T;
	}
	Poly &intt(int n) {
		return ::intt(begin(), n), T;
	}
	static Poly &mul(Poly &f, Poly &g, int n) {
		f.ntt(n), g.ntt(n);
		for (int i = 0; i < n; i++)
			f[i] = 1ll * f[i] * g[i] % P;
		return f.intt(n);
	}
	friend Poly operator*(Poly f, Poly g) {
		int m = f.deg() + g.deg() - 1;
		return mul(f, g, get_lim(m)).redeg(m);
	}
	Poly deriv() const;
	Poly integr() const;
	Poly inv(int m) const;
	Poly div(int m, const Poly &g) const;
	Poly ln(int m) const;
	Poly exp(int m) const;
	Poly sqrt(int m) const;
	Poly pow(int m, int k) const;
	Poly rev() const {
		return {rbegin(), rend()};
	}
	friend Poly operator/(const Poly &f, const Poly &g);
#undef T
};
