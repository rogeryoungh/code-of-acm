#include "basic/index.hpp"

#include "poly/ntt-newton.cpp"

Poly pow_safe(const Poly &g, int m, ll k)  {
	int pos = 0;
	while (pos < g.deg() && g[pos].v == 0) {
		++pos;
	}
	if (pos == g.deg() || pos > (m - 1) / k) {
		return Poly(m, 0);
	}
	Z x = g[pos];
	Poly f = Poly(g.begin() + pos, g.end()) * x.inv();
	f = f.pow(m - pos * k, k % P) * x.pow(k % (P - 1));
	f.insert(f.begin(), pos * k, 0);
	assert(f.deg() == m);
	return f;
}
