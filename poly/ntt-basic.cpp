#include "basic/index.hpp"

#include "math-modint/pre-all.cpp"

// @description 多项式牛顿迭代(m32)
// @problem https://loj.ac/p/150

V<Z> w{1, 1};

inline int get_lim(int m) {
	return 1 << std::__lg(m * 2 - 1);
}

void pre_w(int n) {
	int l = w.size(), l2 = l * 2;
	if (n <= l)
		return;
	w.resize(l2);
	Z p = Z(3).pow((P - 1) / l2);
	for (int i = l; i < l2; i += 2) {
		w[i] = w[i / 2];
		w[i + 1] = w[i] * p;
	}
	pre_w(n);
}

static int ntt_size = 0;

void ntt(auto f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = n / 2; l; l /= 2)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				Z x = f[i + j], y = f[i + j + l];
				f[i + j + l] = w[j + l] * (x - y);
				f[i + j] = x + y;
			}
}

void intt(auto f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = 1; l < n; l *= 2)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				Z x = f[i + j], y = w[j + l] * f[i + j + l];
				f[i + j] = x + y, f[i + j + l] = x - y;
			}
	const int ivn = P - (P - 1) / n;
	for (int i = 0; i < n; i++)
		f[i] *= ivn;
	std::reverse(f + 1, f + n);
}

struct Poly : V<Z> { // 大常数板子
	using vector::vector;
#define T (*this)
	int deg() const {
		return size();
	}
	Poly &redeg(int m) {
		return resize(m), T;
	}
	Poly cut(int m, int l = 0) const {
		return {begin() + l, begin() + std::min(m + l, deg())};
	}
	Poly &operator+=(const Poly &g) {
		redeg(std::max(deg(), g.deg()));
		for (int i = 0; i < g.deg(); i++)
			T[i] += g[i];
		return T;
	}
	Poly &operator-=(const Poly &g) {
		redeg(std::max(deg(), g.deg()));
		for (int i = 0; i < g.deg(); i++)
			T[i] -= g[i];
		return T;
	}
	Poly &operator*=(Z k) {
		for (Z &fi : T)
			fi *= k;
		return T;
	}
	OPERATOR(Poly, Poly, +);
	OPERATOR(Poly, Poly, -);
	OPERATOR(Poly, Z, *);
	OPERATOR(Poly, Poly, *);
	Poly &ntt(int n) {
		return redeg(n), ::ntt(begin(), n), T;
	}
	Poly &intt(int n) {
		return ::intt(begin(), n), T;
	}
	static Poly &mul(Poly &f, Poly &g, int n) {
		f.ntt(n), g.ntt(n);
		for (int i = 0; i < n; i++)
			f[i] *= g[i];
		return f.intt(n);
	}
	Poly &operator*=(Poly g) {
		int m = T.deg() + g.deg() - 1;
		return mul(T, g, get_lim(m)).redeg(m);
	}
	Poly rev() const {
		return {rbegin(), rend()};
	}
#undef T
};
