#include "basic/index.hpp"

#include "math/pre-all/pre-all-modint.hpp"

// @description 多项式牛顿迭代(m32, 卡常)
// @problem https://loj.ac/p/150

std::vector<Z> w{1, 1};

inline int get_lim(int m) {
	return 1 << std::__lg(m * 2 - 1);
}

void pre_w(int n) {
	int l = w.size(), l2 = l * 2;
	if (n <= l)
		return;
	w.resize(l2);
	Z p = qpow(3, (P - 1) / l2);
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

struct Poly : std::vector<Z> { // 卡常板子
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
	Poly inv(int m) const;
	Poly div(int m, Poly g) const;
	Poly ln(int m) const {
		return deriv(m).div(m, cut(m)).integr(m);
	}
	Poly exp(int m) const;
	Poly sqrt(int m) const;
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

Poly Poly::inv(int u) const { // 10E
	if (u == 1) {
		return {front().inv()};
	}
	const int R = 16;
	int m = get_lim((u - 1) / R + 1);
	Poly x = inv(m);
	vector<Poly> nf(R), ng(R);
	nf[0] = cut(m).ntt(m * 2);
	for (int k = 1; x.deg() < u; k++) {
		nf[k] = cut(m, k * m).ntt(m * 2);			  // 2E
		ng[k - 1] = x.cut(m, (k - 1) * m).ntt(m * 2); // 2E
		Poly psi(m * 2);
		for (int j = 0; j < k; j++) {
			for (int i = 0; i < m; i++)
				psi[i] -= ng[j][i] * (nf[k - j][i] + nf[k - 1 - j][i]);
			for (int i = m; i < m * 2; i++)
				psi[i] -= ng[j][i] * (nf[k - j][i] - nf[k - 1 - j][i]);
		}
		psi.intt(m * 2).fill0H(m * 2); // 2E
		mul(psi, ng[0], m * 2);		   // 4E
		x.redeg((k + 1) * m);
		for (int i = 0; i < m; i++)
			x[m * k + i] = psi[i];
	}
	return x.cut(u);
}

Poly Poly::sqrt(int u) const { // 8E
	if (u == 1) {
		return {1};
	}
	const int R = 16;
	int m = get_lim((u - 1) / R + 1);
	Poly x = sqrt(m), h = x.inv(m).ntt(m * 2);
	vector<Poly> ng(R);

	for (int k = 1; x.deg() < u; k++) {
		ng[k - 1] = x.cut(m, (k - 1) * m).ntt(m * 2);
		Poly psi(m * 2);
		for (int j = 0; j < k; j++) {
			if (j >= 1) {
				for (int i = 0; i < m; i++)
					psi[i] -= ng[j][i] * (ng[k - j][i] + ng[k - 1 - j][i]);
				for (int i = m; i < m * 2; i++)
					psi[i] -= ng[j][i] * (ng[k - j][i] - ng[k - 1 - j][i]);
			} else {
				for (int i = 0; i < m; i++)
					psi[i] -= ng[j][i] * ng[k - 1 - j][i];
				for (int i = m; i < m * 2; i++)
					psi[i] += ng[j][i] * ng[k - 1 - j][i];
			}
		}
		psi.intt(m * 2).fill0H(m * 2);
		for (int j = 0; j < std::min(m, deg() - m * k); j++)
			psi[j] += (*this)[m * k + j];
		mul(psi, h, m * 2);
		x.redeg((k + 1) * m);
		for (int i = 0; i < m; i++)
			x[m * k + i] = psi[i] * iv[2];
	}
	return x.cut(u);
}

Poly Poly::div(int u, Poly f) const { // 10E
	if (u == 1) {
		return {front() * f[0].inv()};
	}
	f.redeg(u);
	const int R = 16;
	int m = get_lim((u - 1) / R + 1);
	Poly x = div(m, f), h = f.inv(m).ntt(m * 2);

	vector<Poly> nf(R), ng(R);

	nf[0] = f.cut(m).ntt(m * 2);
	for (int k = 1; x.deg() < u; k++) {
		nf[k] = f.cut(m, k * m).ntt(m * 2);
		ng[k - 1] = x.cut(m, (k - 1) * m).ntt(m * 2);
		Poly psi(m * 2);
		for (int j = 0; j < k; j++) {
			for (int i = 0; i < m; i++)
				psi[i] -= ng[j][i] * (nf[k - j][i] + nf[k - 1 - j][i]);
			for (int i = m; i < m * 2; i++)
				psi[i] -= ng[j][i] * (nf[k - j][i] - nf[k - 1 - j][i]);
		}
		psi.intt(m * 2).fill0H(m * 2);
		for (int j = 0; j < std::min(m, deg() - m * k); j++)
			psi[j] += (*this)[m * k + j];
		mul(psi, h, m * 2);
		x.redeg((k + 1) * m);
		for (int i = 0; i < m; i++)
			x[m * k + i] = psi[i];
	}
	return x.cut(u);
}

Poly Poly::exp(int u) const { // 14E
	if (u == 1) {
		return {1};
	}
	const int R = 16;
	int m = get_lim((u - 1) / R + 1);
	Poly x = exp(m), y = x.inv(m);
	vector<Poly> nf(R), ng(R);

	Poly df = *this;
	for (int i = 0; i < df.deg(); i++)
		df[i] *= i;
	y.ntt(m * 2);
	nf[0] = df.cut(m).ntt(m * 2);

	for (int k = 1; x.deg() < u; k++) {
		nf[k] = df.cut(m, k * m).ntt(m * 2);
		ng[k - 1] = x.cut(m, m * (k - 1)).ntt(m * 2);
		Poly psi(m * 2);
		for (int j = 0; j < k; j++) {
			for (int i = 0; i < m; i++)
				psi[i] += ng[j][i] * (nf[k - j][i] + nf[k - 1 - j][i]);
			for (int i = m; i < m * 2; i++)
				psi[i] += ng[j][i] * (nf[k - j][i] - nf[k - 1 - j][i]);
		}
		psi.intt(m * 2).fill0H(m * 2);

		mul(psi, y, m * 2).fill0H(m * 2);
		for (int i = 0; i < m * 2; i++)
			psi[i] *= iv[m * k + i];
		mul(psi, ng[0], m * 2).fill0H(m * 2);
		x.redeg((k + 1) * m);
		for (int i = 0; i < m; i++)
			x[m * k + i] = psi[i];
	}
	return x.cut(u);
}
