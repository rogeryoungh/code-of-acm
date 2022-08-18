
Poly pow_safe(int m, ll k) const {
	int pos = 0;
	while (pos < deg() && T[pos].v == 0) {
		++pos;
	}
	if (pos == deg() || pos > (m - 1) / k) {
		return Poly(m, 0);
	}
	Z x = T[pos];
	Poly f = Poly(begin() + pos, end()) * x.inv();
	f = f.pow(m - pos * k, k % P) * x.pow(k % (P - 1));
	f.insert(f.begin(), pos * k, 0);
	assert(f.deg() == m);
	return f;
}

