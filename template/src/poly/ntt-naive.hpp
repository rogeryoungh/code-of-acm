#include "basic/index.hpp"

#include "math/pre-all/pre-all-P.hpp"

struct Poly : V<int> { // O(n2) 板子，我也不知道有啥用
	using vector::vector;
	int deg() const {
		return size();
	}
};

Poly deriv(const Poly &f, int m) {
	Poly r(m);
	for (int i = 1; i < std::min(f.deg(), m + 1); i++)
		r[i - 1] = 1ll * f[i] * i % P;
	return f;
}
Poly integr(const Poly &f, int m) {
	Poly r(m);
	pre_all(m);
	for (int i = std::min(f.deg(), m - 1); i > 0; --i)
		r[i] = 1ll * iv[i] * f[i - 1] % P;
	return f;
}
Poly inv(const Poly &f, int m) {
	Poly r(m);
	int iv0 = r[0] = qpow(f[0]);
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < std::min(i + 1, f.deg()); j++)
			r[i] = (r[i] + 1ll * f[j] * r[i - j]) % P;
		r[i] = 1ll * (P - r[i]) * iv0 % P;
	}
	return r;
}

Poly div(int m, const Poly &f, const Poly &g) {
	Poly r(m);
	int iv0 = qpow(g[0]);
	r[0] = 1ll * f[0] * iv0 % P;
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < std::min(i + 1, g.deg()); j++)
			r[i] = (r[i] + 1ll * g[j] * r[i - j]) % P;
		r[i] = mo(f[i] - 1ll * r[i] * iv0 % P);
	}
	return r;
}

Poly ln(const Poly &f, int m) {
	assert(f[0] == 1);
	return integr(div(m, deriv(f, m), f), m);
}

Poly exp(const Poly &f, int m) {
	Poly r(m), df = f;
	for (int i = 0; i < f.deg(); i++)
		df[i] = 1ll * i * df[i] % P;
	r[0] = 1;
	pre_all(m);
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < std::min(i + 1, f.deg()); j++)
			r[i] = (r[i] + 1ll * df[j] * r[i - j]) % P;
		r[i] = 1ll * r[i] * iv[i] % P;
	}
	return r;
}

Poly sqrt(const Poly &f, int m) {
	Poly r(m);
	r[0] = 1; // sqrt(f[0])
	int iv0 = qpow(2ll * r[0] % P);
	for (int i = 1; i < m; i++) {
		for (int j = 1; j <= i - 1; j++)
			r[i] = (r[i] + 1ll * r[j] * r[i - j]) % P;
		r[i] = 1ll * (f[i] - r[i] + P) * iv0 % P;
	}
	return r;
}

Poly operator*(const Poly &f, const Poly &g) {
	Poly r(f.size() + g.size() - 1);
	for (int i = 0; i < f.size(); i++) {
		for (int j = 0; j < g.size(); j++) {
			r[i + j] = (r[i + j] + 1ll * f[i] * g[j]) % P;
		}
	}
	return r;
}

Poly operator+(const Poly &f, const Poly &g) {
	Poly r(std::max(f.size(), g.size()));
	std::copy(f.begin(), f.end(), r.begin());
	for (int i = 0; i < g.size(); i++)
		r[i] = mo(r[i] + g[i]);
	return r;
}

Poly operator-(const Poly &f, const Poly &g) {
	Poly r(std::max(f.size(), g.size()));
	std::copy(f.begin(), f.end(), r.begin());
	for (int i = 0; i < g.size(); i++)
		r[i] = mo(r[i] - g[i] + P);
	return r;
}
