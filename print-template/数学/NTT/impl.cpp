Poly deriv(int m) const {
	Poly f(m);
	for (int i = 1; i < min(deg(), m + 1); i++)
		f[i - 1] = T[i] * i;
	return f;
}
Poly integr(int m) const {
	Poly f(m);
	for (int i = min(deg(), m - 1); i > 0; --i)
		f[i] = iv[i] * T[i - 1];
	return f;
}
Poly inv(int m) const { // 12E
	Poly x = {T[0].inv()};
	for (int t = 2; t < m * 2; t *= 2) {
		Poly u = cut(t).ntt(t * 2);
		x.ntt(t * 2);
		for (int i = 0; i < t * 2; i++)
			x[i] = (2 - u[i] * x[i]) * x[i];
		x.intt(t * 2).redeg(t);
	}
	return x.redeg(m);
}
Poly div(int m, const Poly &g) const { // 18E
	if (deg() == 0)
		return {};
	return (cut(m) * g.inv(m)).redeg(m);
}
Poly ln(int m) const {
	assert(T[0].v == 1);
	return deriv(m).div(m - 1, cut(m)).integr(m);
}
Poly exp(int m) const { // 48E
	assert(T[0].v == 0);
	Poly x = {1};
	for (int t = 2; t < m * 2; t *= 2) {
		x = x * (cut(t) - x.ln(t) + Poly{1}), x.redeg(t);
	}
	return x.redeg(m);
}
Poly sqrt(int m) const { // 36E
	Poly x = {1};
	for (int t = 2; t < m * 2; t *= 2) {
		x = (x + cut(t).div(t, x)) * qpow(2);
	}
	return x.redeg(m);
}
Poly pow(int m, int k) const {
	return (ln(m) * k).exp(m);
}
Poly rev() const {
	return {rbegin(), rend()};
}
Poly shift(int c) {
	int n = deg();
	Poly A(n), B(n);
	Z ci = 1;
	for (int i = 0; i < n; i++) {
		A[i] = T[i] * fac[i];
		B[i] = ci * ifac[i];
		ci *= c;
	}
	reverse(A.begin(), A.end());
	A = A * B;
	for (int i = 0; i < n; i++) {
		B[i] = A[n - i - 1] * ifac[i];
	}
	return B;
}
friend Poly operator/(const Poly &f, const Poly &g) {
	int m = f.deg() - g.deg() + 1;
	return f.rev().div(m, g.rev()).rev();
}
