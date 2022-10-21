#include "basic/index.hpp"

#include "math-modint/basic.cpp"

// @description 多项式牛顿迭代(m32)
// @problem https://loj.ac/p/150

std::vector<Z> w{1, 1}, iv{1, 1}, fac{1}, ifac{1};

inline int get_lim(int m) {
	return 2 << std::__lg(m - (m > 1));
}

void pre_w(int n) {
	int lim = w.size();
	n = get_lim(n);
	if (n <= lim)
		return;
	w.resize(n);
	for (int l = lim; l < n; l *= 2) {
		Z p = qpow(3, (P - 1) / l / 2);
		for (int i = 0; i < l; i += 2) {
			w[(l + i)] = w[(l + i) / 2];
			w[l + i + 1] = w[l + i] * p;
		}
	}
	lim = n;
}

void pre_all(int n) {
	iv = fac = ifac = std::vector<Z>(n + 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = i * fac[i - 1];
	}
	ifac[n] = fac[n].inv(), iv[n] = Z(n).inv();
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1);
		iv[i] = ifac[i] * fac[i - 1];
	}
}

Z C(int n, int m) {
	return fac[n] * ifac[m] * ifac[n - m];
}

static int ntt_size = 0;

template <class iter>
void ntt(iter f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = n / 2; l; l >>= 1)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				Z x = f[i + j], y = f[i + j + l];
				f[i + j + l] = w[j + l] * (x - y);
				f[i + j] = x + y;
			}
}

template <class iter>
void intt(iter f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = 1; l < n; l <<= 1)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				Z x = f[i + j], y = w[j + l] * f[i + j + l];
				f[i + j] = x + y, f[i + j + l] = x - y;
			}
	const int ivn = P - (P - 1) / n;
	for (int i = 0; i < n; i++)
		f[i] *= ivn;
	reverse(f + 1, f + n);
}

struct Poly : std::vector<Z> { // 大常数板子
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
	friend Poly operator*(Poly f, Poly g) {
		int m = f.deg() + g.deg() - 1;
		return mul(f, g, get_lim(m)).redeg(m);
	}
	Poly deriv(int m) const {
		Poly f(m);
		for (int i = 1; i < std::min(deg(), m + 1); i++)
			f[i - 1] = T[i] * i;
		return f;
	}
	Poly integr(int m) const {
		Poly f(m);
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
		return deriv(m).div(m - 1, cut(m)).integr(m);
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
			x = (x + cut(t).div(t, x)) * qpow(2);
		}
		return x.redeg(m);
	}
	Poly pow(int m, int k) const {
		return (ln(m) * k).exp(m);
	}
	Poly rev() const {
		return {rbegin(), rend()};
	}
	Poly shift(int c) {
		int n = deg();
		Poly A(n), B(n);
		Z ci = 1;
		for (int i = 0; i < n; i++) {
			A[i] = T[i] * fac[i];
			B[i] = ci * ifac[i];
			ci *= c;
		}
		reverse(A.begin(), A.end());
		A = A * B;
		for (int i = 0; i < n; i++) {
			B[i] = A[n - i - 1] * ifac[i];
		}
		return B;
	}
	friend Poly operator/(const Poly &f, const Poly &g) {
		int m = f.deg() - g.deg() + 1;
		return f.rev().div(m, g.rev()).rev();
	}
#undef T
};
