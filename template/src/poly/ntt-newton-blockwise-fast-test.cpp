#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include "poly/ntt-newton-blockwise-fast.hpp"

PICOBENCH_SUITE("poly/ntt-newton-blockwise-fast.hpp");

std::vector poly_iterations = {1, 2, 64, 1 << 9, 1 << 12, 1 << 14, 1 << 15, 1 << 16, 1 << 17, 1 << 18, 1 << 19};

static void poly_ntt_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n), pre_w(n);
	Poly f(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P;
	}
	s.start_timer();
	ntt(f.begin(), n);
	s.stop_timer();
}

PICOBENCH(poly_ntt_bench).iterations(poly_iterations).baseline().label("NTT 1E");

static void poly_mul_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n), pre_w(n);
	Poly f(n), g(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P, g[i] = rng() % P;
	}
	s.start_timer();
	f = f * g;
	s.stop_timer();
}

PICOBENCH(poly_mul_bench).iterations(poly_iterations).label("MUL 6E");

static void poly_inv_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n), pre_w(n);
	Poly f(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P;
	}
	f[0] = rng() % (P - 1) + 1;
	s.start_timer();
	f = f.inv(n);
	s.stop_timer();
}

PICOBENCH(poly_inv_bench).iterations(poly_iterations).label("INV 10E");

static void poly_ln_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n), pre_w(n);
	Poly f(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P;
	}
	f[0] = 1;
	s.start_timer();
	f = f.ln(n);
	s.stop_timer();
}

PICOBENCH(poly_ln_bench).iterations(poly_iterations).label("LOG 10E");

static void poly_exp_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n), pre_w(n);
	Poly f(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P;
	}
	s.start_timer();
	f = f.exp(n);
	s.stop_timer();
}

PICOBENCH(poly_exp_bench).iterations(poly_iterations).label("EXP 14E");

static void poly_sqrt_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n), pre_w(n);
	Poly f(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P;
	}
	s.start_timer();
	f = f.sqrt(n);
	s.stop_timer();
}

PICOBENCH(poly_sqrt_bench).iterations(poly_iterations).label("SQRT 8E");
