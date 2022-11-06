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
	Poly deriv(int m) const {
		Poly f(m);
		pre_all(m);
		for (int i = 1; i < std::min(deg(), m + 1); i++)
			f[i - 1] = T[i] * i;
		return f;
	}
	Poly integr(int m) const {
		Poly f(m);
		pre_all(m);
		for (int i = std::min(deg(), m - 1); i > 0; --i)
			f[i] = iv[i] * T[i - 1];
		return f;
	}
	Poly inv(int m) const { // 12E
		Poly x = {T[0].inv()};
		for (int t = 2; t < m * 2; t *= 2) {
			Poly u = cut(t).ntt(t * 2);
			x.ntt(t * 2);
			for (int i = 0; i < t * 2; i++)
				x[i] = (2 - u[i] * x[i]) * x[i];
			x.intt(t * 2).redeg(t);
		}
		return x.redeg(m);
	}
	Poly div(int m, const Poly &g) const { // 18E
		if (deg() == 0)
			return {};
		return (cut(m) * g.inv(m)).redeg(m);
	}
	Poly ln(int m) const {
		assert(T[0].v == 1);
		return deriv(m).div(m, cut(m)).integr(m);
	}
	Poly exp(int m) const { // 48E
		assert(T[0].v == 0);
		Poly x = {1};
		for (int t = 2; t < m * 2; t *= 2) {
			x = x * (cut(t) - x.ln(t) + Poly{1}), x.redeg(t);
		}
		return x.redeg(m);
	}
	Poly sqrt(int m) const { // 36E
		Poly x = {1};
		for (int t = 2; t < m * 2; t *= 2) {
			x = (x + cut(t).div(t, x)) * ((P + 1) / 2);
		}
		return x.redeg(m);
	}
	Poly pow(int m, int k) const {
		return (ln(m) * k).exp(m);
	}
	Poly rev() const {
		return {rbegin(), rend()};
	}
	friend Poly operator/(const Poly &f, const Poly &g) {
		int m = f.deg() - g.deg() + 1;
		return f.rev().div(m, g.rev()).rev();
	}
	friend auto operator%(const Poly &f, const Poly &g) {
		Poly Q = f / g;
		return make_pair(Q, (f - Q * g).redeg(g.deg() - 1));
	}
#undef T
};
