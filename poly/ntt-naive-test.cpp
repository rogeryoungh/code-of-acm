#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include "poly/ntt-naive.hpp"

PICOBENCH_SUITE("poly/ntt-naive.hpp");

std::vector poly_iterations = {1, 2, 64, 1 << 9, 1 << 12, 1 << 14};

static void poly_mul_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n);
	Poly f(n), g(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P, g[i] = rng() % P;
	}
	s.start_timer();
	f = f * g;
	s.stop_timer();
}

PICOBENCH(poly_mul_bench).iterations(poly_iterations).label("MUL");

static void poly_inv_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n);
	Poly f(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P;
	}
	f[0] = rng() % (P - 1) + 1;
	s.start_timer();
	f = inv(f, n);
	s.stop_timer();
}

PICOBENCH(poly_inv_bench).iterations(poly_iterations).label("INV");

static void poly_exp_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n);
	Poly f(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P;
	}
	s.start_timer();
	f = exp(f, n);
	s.stop_timer();
}

PICOBENCH(poly_exp_bench).iterations(poly_iterations).label("EXP");

static void poly_sqrt_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n);
	Poly f(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P;
	}
	s.start_timer();
	f = sqrt(f, n);
	s.stop_timer();
}

PICOBENCH(poly_sqrt_bench).iterations(poly_iterations).label("SQRT");
