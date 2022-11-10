#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include "poly/ntt-newton.cpp"

PICOBENCH_SUITE("poly/ntt-newton.cpp");

std::vector poly_iterations = {1, 2, 4, 8, 16, 64, 512, 1 << 16, 1 << 17};

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

PICOBENCH(poly_ntt_bench).samples(5).iterations(poly_iterations).baseline().label("NTT 1E");

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

PICOBENCH(poly_mul_bench).samples(5).iterations(poly_iterations).label("MUL 3E");

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

PICOBENCH(poly_inv_bench).samples(5).iterations(poly_iterations).label("INV 12E");

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

PICOBENCH(poly_exp_bench).samples(5).iterations(poly_iterations).label("EXP 48E");

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

PICOBENCH(poly_sqrt_bench).samples(5).iterations(poly_iterations).label("SQRT 36E");

// int main(int argc, char *argv[]) {
// 	picobench::runner r;
// 	r.parse_cmd_line(argc, argv);
// 	if (r.should_run()) {
// 		r.run_benchmarks();
// 		auto report = r.generate_report();
// 		std::ofstream out("./fuck.info", std::ios::out);
// 		report.to_text(out);
// 	}
// 	return r.run();
// }
