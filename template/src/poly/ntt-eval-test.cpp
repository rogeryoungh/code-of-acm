#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include "poly/ntt-eval.hpp"

PICOBENCH_SUITE("poly/ntt-eval.hpp");

std::vector poly_iterations = {1, 2, 64, 1 << 9, 1 << 12, 1 << 14, 1 << 15, 1 << 16, 1 << 17};

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

static void poly_eval_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n), pre_w(n);
	Poly f(n), x(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		f[i] = rng() % P, x[i] = rng() % P;
	}
	s.start_timer();
	f = PolyEI(x).eval(f);
	s.stop_timer();
}

PICOBENCH(poly_eval_bench).iterations(poly_iterations).label("EVAL");

static void poly_inter_bench(picobench::state &s) {
	int n = s.iterations();
	pre_all(n), pre_w(n);
	Poly y(n), x(n);
	std::mt19937 rng(58);
	for (int i = 0; i < n; i++) {
		y[i] = rng() % P, x[i] = rng() % P;
	}
	s.start_timer();
	auto f = PolyEI(x).inter(y);
	s.stop_timer();
}

PICOBENCH(poly_eval_bench).iterations(poly_iterations).label("INTER");
