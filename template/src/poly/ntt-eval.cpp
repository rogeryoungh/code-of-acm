#include <vector>
#include <algorithm>
using namespace std;

// @description 多项式多点求值
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
	Z &operator=(const int &m) {
		v = m;
		return *this;
	}
	Z pow(int n) const {
		return qpow(v, n, P);
	}
	Z inv() const {
		return qpow(v);
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
	Z &operator/=(const Z &m) {
		return *this *= m.inv();
	}
	OPERATOR(Z, +);
	OPERATOR(Z, -);
	OPERATOR(Z, *);
	OPERATOR(Z, /);
	Z operator-() const {
		return v == 0 ? 0 : P - v;
	}
	static int mod() {
		return P;
	}
};

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

Z choose(int n, int m) {
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

struct Poly : vector<Z> { // 大常数板子
	using vector::vector;
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
	Poly operator*(int k) {
		Poly f = T;
		for (Z &fi : f)
			fi *= k;
		return f;
	}
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
	Poly deriv() const {
		Poly f(deg() - 1);
		for (int i = 1; i < deg(); i++)
			f[i - 1] = T[i] * i;
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
	Poly rev() const {
		return {rbegin(), rend()};
	}
	friend Poly operator/(const Poly &f, const Poly &g) {
		int m = f.deg() - g.deg() + 1;
		return f.rev().div(m, g.rev()).rev();
	}
#undef T
};

struct PolyEI {
	int raw_n, n;
	vector<Poly> p;
	PolyEI(Poly a) : raw_n(a.deg()), n(get_lim(raw_n)), p(n * 2) {
		a.redeg(n);
		for (int i = 0; i < n; i++)
			p[i + n] = {1, -a[i]};
		for (int i = n - 1; i; i--) {
			int ls = i * 2, rs = i * 2 + 1;
			int len = get_lim(p[ls].deg());
			p[ls].ntt(len), p[rs].ntt(len), p[i].redeg(len);
			for (int j = 0; j < len; j++)
				p[i][j] = p[ls][j] * p[rs][j];
			p[i].intt(len);
			p[i].push_back(p[i][0] - 1), p[i][0] = 1;
		}
	}
	Poly eval(const Poly &f) { // PolyEI(x).eval(f)
		int m = f.deg();
		if (m == 1)
			return Poly(raw_n, f[0]);
		Poly q = f.rev().div(m, p[1]).redeg(n);
		rotate(q.begin(), q.begin() + m, q.end());
		for (int k = n, o = 1; k > 1; k >>= 1)
			for (int i = 0; i < n; i += k, o++) {
				if (i >= raw_n)
					continue;
				Poly foo(k), bar(k);
				auto qi = q.begin() + i;
				ntt(qi, k);
				for (int j = 0; j < k; j++) {
					foo[j] = qi[j] * p[o * 2 + 1][j];
					bar[j] = qi[j] * p[o * 2][j];
				}
				foo.intt(k), bar.intt(k);
				copy(foo.begin() + k / 2, foo.end(), qi);
				copy(bar.begin() + k / 2, bar.end(), qi + k / 2);
			}
		return q.cut(raw_n);
	}
	Poly inter(const Poly &y) { // PolyEI(x).inter(y)
		Poly q = Poly(p[1]).redeg(raw_n + 1);
		q = eval(q.rev().deriv()).redeg(n);
		for (int i = 0; i < raw_n; i++)
			q[i] = y[i] / q[i];
		for (int k = 1, h = n / 2; k < n; k *= 2, h >>= 1)
			for (int i = 0, o = h; i < n; i += k * 2, o++) {
				if (i >= raw_n)
					continue;
				auto qi = q.begin() + i;
				Poly foo(qi, qi + k), bar(qi + k, qi + k * 2);
				foo.ntt(k * 2), bar.ntt(k * 2);
				for (int j = 0; j < k * 2; j++) {
					qi[j] = foo[j] * p[o * 2 + 1][j] + bar[j] * p[o * 2][j];
				}
				intt(qi, k * 2);
			}
		return q.cut(raw_n).rev();
	}
};