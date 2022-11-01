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
		x = (x + cut(t).div(t, x)) * ((P + 1) / 2);
	}
	return x.redeg(m);
}
Poly pow(int m, int k) const {
	return (ln(m) * k).exp(m);
}
Poly rev() const {
	return {rbegin(), rend()};
}
friend Poly operator/(const Poly &f, const Poly &g) {
	int m = f.deg() - g.deg() + 1;
	return f.rev().div(m, g.rev()).rev();
}
friend auto operator%(const Poly &f, const Poly &g) {
	Poly Q = f / g;
	return make_pair(Q, (f - Q * g).redeg(g.deg() - 1));
}
