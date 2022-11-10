#include "basic/index.hpp"

#include "math-modint/pre-all.hpp"

// @description 多项式牛顿迭代(m32, 卡常)
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

struct Poly : V<Z> { // 卡常板子
	using vector::vector;
	bool isNTT = false;
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
		if (!isNTT) {
			redeg(n), ::ntt(begin(), n);
			isNTT = true;
		}
		return T;
	}
	Poly &intt(int n) {
		isNTT = false;
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
		pre_all(deg());
		for (int i = std::min(deg(), m - 1); i > 0; --i)
			f[i] = iv[i] * T[i - 1];
		return f;
	}
	Poly &fill0L(int m) {
		fill_n(begin(), m / 2, 0);
		return T;
	}
	Poly &fill0H(int m) {
		fill_n(begin() + m / 2, m / 2, 0);
		return T;
	}
	Poly &invD(Poly f2, Poly nx, int t) {
		mul(f2, nx, t).fill0L(t); // 6E
		mul(f2, nx, t);			  // 4E
		redeg(t);
		for (int i = t / 2; i < t; i++) {
			T[i] = -f2[i];
		}
		return T;
	}
	Poly inv(int m) const { // 10E
		Poly x = {qpow(T[0].v)};
		for (int t = 2; t < m * 2; t *= 2) {
			x.invD(cut(t), x.cut(m), t);
		}
		return x.redeg(m);
	}
	Poly div(int m, Poly g) const { // 13E
		if (deg() == 0)
			return {};
		int t = get_lim(m);
		Poly x = cut(t / 2), u = g.inv(t / 2); // 10E
		Poly q = mul(x, u, t).cut(t / 2);	   // 6E
		mul(q, g, t).fill0L(t);				   // 6E
		for (int i = t / 2; i < std::min(t, deg()); i++)
			q[i] -= T[i];
		mul(q, u, t); // 4E
		for (int i = t / 2; i < t; i++)
			x[i] = -q[i];
		return x.cut(m);
	}
	Poly ln(int m) const {
		return deriv(m).div(m, cut(m)).integr(m);
	}
	Poly exp(int m) const { // 17E
		if (m == 1)
			return {1};
		Poly f = {1, T[1]}, g = {1}, nf, ng = g;
		pre_all(deg());
		for (int t = 4; t < m * 2; t *= 2) {
			nf = Poly(f).ntt(t);		// 2E
			ng = g.invD(nf, ng, t / 2); // 3E
			Poly q = cut(t / 2);
			for (int i = 0; i < q.deg(); i++)
				q[i] *= i;
			mul(q, nf, t / 2); // 2E
			for (int i = 0; i < t / 2; i++)
				q[i] -= i * f[i];
			mul(q, ng, t); // 6E
			for (int i = t / 2; i < std::min(t, deg()); i++)
				q[i] = T[i] + q[i - t / 2] * iv[i];
			mul(q.fill0L(t), nf, t); // 4E
			f.redeg(t);
			for (int i = t / 2; i < t; i++)
				f[i] = q[i];
		}
		return f.cut(m);
	}
	Poly sqrt(int m) const { // 11E
		Poly x = {1}, g = x.inv(1), ng = g;
		for (int t = 2; t < m * 2; t *= 2) {
			Poly f = Poly(x).ntt(t / 2); // 2E
			if (t >= 4)
				ng = g.invD(f, ng, t / 2); // 3E
			mul(f, f, t / 2).redeg(t);	   // 1E
			for (int i = t / 2; i < std::min(t, deg()); i++)
				f[i] = T[i - t / 2] + T[i] - f[i - t / 2];
			mul(f.fill0L(t), ng, t); // 6E
			x.redeg(t);
			for (int i = t / 2; i < t; i++)
				x[i] = f[i] * ((P + 1) / 2);
		}
		return x.cut(deg());
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
#undef T
};
