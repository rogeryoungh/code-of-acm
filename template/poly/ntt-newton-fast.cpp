#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;
using ll = int64_t;

// @description 多项式牛顿迭代(m32, 卡常)
// @problem https://loj.ac/p/150

const int P = 998244353;

int qpow(int a, int b = P - 2, int m = P) {
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

#define OPERATOR(U, op)                                       \
	friend inline U operator op(const U &lhs, const U &rhs) { \
		return U(lhs) op## = rhs;                             \
	}

struct Z {
	int v;
	Z(int a = 0) : v(a) {}
	Z(ll a) : v(a % P) {}
	Z &operator=(const int &m) {
		v = m;
		return *this;
	}
	Z &operator+=(const Z &m) {
		v = (v += m.v) >= P ? v - P : v;
		return *this;
	}
	Z &operator-=(const Z &m) {
		v = (v -= m.v) < 0 ? v + P : v;
		return *this;
	}
	Z &operator*=(const Z &m) {
		v = 1ll * v * m.v % P;
		return *this;
	}
	OPERATOR(Z, +);
	OPERATOR(Z, -);
	OPERATOR(Z, *);
	Z pow(int n) const {
		int ret = P != 1, a = v;
		for (; n; n /= 2) {
			if (n % 2 == 1)
				ret = 1ll * ret * a % P;
			a = 1ll * a * a % P;
		}
		return ret;
	}
	Z inv() const {
		return pow(P - 2);
	}
	// useless
	Z operator-() const {
		return v == 0 ? 0 : P - v;
	}
	Z &operator/=(const Z &m) {
		return *this *= m.inv();
	}
	OPERATOR(Z, /);
};

istream &operator>>(istream &is, Z &z) {
	return is >> z.v;
}

ostream &operator<<(ostream &os, const Z &z) {
	return os << z.v;
}

vector<Z> w{1, 1}, iv{1, 1}, fac{1}, ifac{1};

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
	iv.resize(n + 1), fac.resize(n + 1), ifac.resize(n + 1);
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

struct Poly : vector<Z> { // 卡常板子
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
		return {begin() + l, begin() + min(m + l, deg())};
	}
	Poly &operator+=(const Poly &g) {
		redeg(max(deg(), g.deg()));
		for (int i = 0; i < g.deg(); i++)
			T[i] += g[i];
		return T;
	}
	Poly &operator-=(const Poly &g) {
		redeg(max(deg(), g.deg()));
		for (int i = 0; i < g.deg(); i++)
			T[i] -= g[i];
		return T;
	}
	OPERATOR(Poly, +);
	OPERATOR(Poly, -);
	Poly operator*(Z k) {
		Poly f = T;
		for (Z &fi : f)
			fi *= k;
		return f;
	}
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
		for (int i = 1; i < min(deg(), m + 1); i++)
			f[i - 1] = T[i] * i;
		return f;
	}
	Poly integr(int m) const {
		Poly f(m);
		for (int i = min(deg(), m - 1); i > 0; --i)
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
		for (int i = t / 2; i < min(t, deg()); i++)
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
		for (int t = 4; t < m * 2; t <<= 1) {
			nf = Poly(f).ntt(t);		// 2E
			ng = g.invD(nf, ng, t / 2); // 3E
			Poly q = cut(t / 2);
			for (int i = 0; i < q.deg(); i++)
				q[i] *= i;
			mul(q, nf, t / 2); // 2E
			for (int i = 0; i < t / 2; i++)
				q[i] -= i * f[i];
			mul(q, ng, t); // 6E
			for (int i = t / 2; i < min(t, deg()); i++)
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
		for (int t = 2; t < m * 2; t <<= 1) {
			Poly f = Poly(x).ntt(t / 2); // 2E
			if (t >= 4)
				ng = g.invD(f, ng, t / 2); // 3E
			mul(f, f, t / 2).redeg(t);				  // 1E
			for (int i = t / 2; i < min(t, deg()); i++)
				f[i] = T[i - t / 2] + T[i] - f[i - t / 2];
			mul(f.fill0L(t), ng, t); // 6E
			x.redeg(t);
			for (int i = t / 2; i < t; i++)
				x[i] = f[i] * iv[2];
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