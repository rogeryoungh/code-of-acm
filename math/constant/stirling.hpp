#include "basic/index.hpp"

#include "poly/ntt-newton.hpp"

#include "poly/ntt-taylor-shift.hpp" // !!only

#include "poly/ntt-newton-safe.hpp" // !!only

Poly stirling1st_row(int n) {
	if (n == 0)
		return {0};
	Poly f = stirling1st_row(n / 2);
	Poly r = f * taylor_shift(f, n / 2);
	if (n % 2 == 1) {
		r *= Poly{n - 1, 1};
	}
	return r;
}

Poly stirling1st_col(int n, int k) {
	n++;
	Poly r = {1, P - 1};
	r = pow_safe(r.ln(n), n, k, k);
	Z xk = Z(P - 1).pow(k) * ifac[k];
	for (int i = 0; i < n; i++) {
		r[i] *= fac[i] * xk;
	}
	return r;
}

Poly stirling2st_row(int n) {
	n++;
	Poly A(n), B(n);
	for (int i = 0; i < n; i++) {
		A[i] = i % 2 == 1 ? -ifac[i] : ifac[i];
		B[i] = Z(i).pow(n - 1) * ifac[i];
	}
	return (A * B).redeg(n);
}

Poly stirling2st_col(int n, int k) {
	if (n < k)
		return Poly(n + 1);
	std::function<Poly(int)> sol = [&](int u) -> Poly {
		if (u == 0)
			return {1};
		Poly f = sol(u / 2);
		f *= taylor_shift(f, P - u / 2);
		if (u % 2 == 1)
			f *= Poly{-u, 1};
		return f;
	};
	Poly f = sol(k).rev().inv(n - k + 1);
	f.insert(f.begin(), k, 0);
	return f;
}
