#include "basic/index.hpp"

#include "poly/ntt-basic.cpp"

Poly taylor_shift(const Poly &f, Z c) {
	int n = f.deg();
	Poly A(n), B(n);
	Z ci = 1;
	for (int i = 0; i < n; i++) {
		A[i] = f[i] * fac[i];
		B[i] = ci * ifac[i];
		ci *= c;
	}
	std::reverse(A.begin(), A.end());
	A = A * B;
	for (int i = 0; i < n; i++) {
		B[i] = A[n - i - 1] * ifac[i];
	}
	return B;
}
