#include "basic/index.hpp"

#include "poly/ntt-basic.cpp"

Poly chirpz(const Poly &f, int m, Z c) {
	int n = f.deg(), N = get_lim(n + m - 1);
	Poly A = f, pw(n + m, 1), ipw(n + m, 1);
	Z ci = c, ivc = c.inv(), ici = ivc;
	for (int i = 2; i < n + m; i++) {
		pw[i] = pw[i - 1] * ci;
		ipw[i] = ipw[i - 1] * ici;
		ci *= c, ici *= ivc;
	}
	for (int i = 0; i < n; i++)
		A[i] *= ipw[i];
	std::reverse(A.begin(), A.end());
	Poly::mul(A, pw, N);
	Poly x(m);
	for (int i = 0; i < m; i++) {
		x[i] = A[i + n - 1] * ipw[i];
	}
	return x;
}
