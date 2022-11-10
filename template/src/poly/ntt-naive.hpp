#include "basic/index.hpp"

#include "math-P/pre-all.hpp"

struct Poly : V<Z> { // n2 板子，我也不知道有啥用
	using vector::vector;
	int deg() const {
		return size();
	}
};

Poly deriv(const Poly &f, int m) {
	Poly r(m);
	for (int i = 1; i < std::min(f.deg(), m + 1); i++)
		r[i - 1] = f[i] * i;
	return f;
}
Poly integr(const Poly &f, int m) {
	Poly r(m);
	for (int i = std::min(f.deg(), m - 1); i > 0; --i)
		r[i] = iv[i] * f[i - 1];
	return f;
}
Poly inv(const Poly &f, int m) {
	Poly r(m);
	Z iv0 = r[0] = f[0].inv();
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < std::min(i + 1, f.deg()); j++)
			r[i] += f[j] * r[i - j];
		r[i] = -r[i] * iv0;
	}
	return r;
}

Poly div(int m, const Poly &f, const Poly &g) {
	Poly r(m);
	Z iv0 = g[0].inv();
	r[0] = f[0] * iv0;
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < std::min(i + 1, g.deg()); j++)
			r[i] += g[j] * r[i - j];
		r[i] = f[i] - r[i] * iv0;
	}
	return r;
}

Poly ln(const Poly &f, int m) {
	assert(f[0].v == 1);
	return integr(div(m, deriv(f, m), f), m);
}

Poly exp(const Poly &f, int m) {
	Poly r(m), df = f;
	for (int i = 0; i < f.deg(); i++)
		df[i] *= i;
	r[0] = 1;
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < std::min(i + 1, f.deg()); j++)
			r[i] += df[j] * r[i - j];
		r[i] = r[i] * iv[i];
	}
	return r;
}

Poly operator*(const Poly &f, const Poly &g) {
	Poly r(f.size() + g.size() - 1);
	for (int i = 0; i < f.size(); i++) {
		for (int j = 0; j < g.size(); j++) {
			r[i + j] += f[i] * g[j];
		}
	}
	return r;
}

Poly operator+(const Poly &f, const Poly &g) {
	Poly r(std::max(f.size(), g.size()));
	for (int i = 0; i < f.size(); i++)
		r[i] += f[i];
	for (int i = 0; i < g.size(); i++)
		r[i] += g[i];
	return r;
}

Poly operator-(const Poly &f, const Poly &g) {
	Poly r(std::max(f.size(), g.size()));
	for (int i = 0; i < f.size(); i++)
		r[i] -= f[i];
	for (int i = 0; i < g.size(); i++)
		r[i] -= g[i];
	return r;
}
