#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include "poly/fft-mul.hpp"

PICOBENCH_SUITE("poly/fft-mul.hpp");

std::vector poly_iterations = {1, 2, 64, 1 << 9, 1 << 12, 1 << 14, 1 << 15, 1 << 16, 1 << 17, 1 << 18, 1 << 19};

static void poly_mul_bench(picobench::state &s) {
	int n = s.iterations(); pre_w(n);
	Poly f(n), g(n);
	std::mt19937 rng(58);
	const int P = 10;
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P, g[i] = rng() % P;
	}
	s.start_timer();
	f = mul(f, g);
	s.stop_timer();
}

PICOBENCH(poly_mul_bench).iterations(poly_iterations).label("MUL");

static void poly_mul_mod_bench(picobench::state &s) {
	int n = s.iterations(); pre_w(n);
	Poly f(n), g(n);
	std::mt19937 rng(58);
	const int P = 1E9 + 7;
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P, g[i] = rng() % P;
	}
	s.start_timer();
	f = mul5(f, g, P);
	s.stop_timer();
}

PICOBENCH(poly_mul_mod_bench).iterations(poly_iterations).label("MUL5 MOD 1E9 + 7");
