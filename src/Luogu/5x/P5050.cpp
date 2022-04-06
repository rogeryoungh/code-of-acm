#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

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

std::vector<int> w{1, 1}, Inv{1, 1}, fac, ifac;

inline int get_lim(int m) {
	return 2 << std::__lg(m - (m > 1));
}

int mo(int u) {
	return u >= P ? u - P : u;
}

void pre_w(int n) {
	static int lim = 2;
	n = get_lim(n);
	if (n <= lim)
		return;
	w.resize(n);
	for (int l = lim; l < n; l *= 2) {
		int p = qpow(3, (P - 1) / l / 2, P);
		for (int i = 0; i < l; i += 2) {
			w[(l + i)] = w[(l + i) / 2];
			w[l + i + 1] = 1ll * w[l + i] * p % P;
		}
	}
	lim = n;
}

void pre_inv(int n) {
	static int lim = 2;
	if (n <= lim)
		return;
	Inv.resize(n);
	for (int i = lim; i < n; i++) {
		Inv[i] = 1ll * Inv[P % i] * (P - P / i) % P;
	}
	lim = n;
}

static int ntt_size = 0;

template <class iter>
void ntt(iter f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = n / 2; l; l >>= 1)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				int x = f[i + j], y = f[i + j + l];
				f[i + j + l] = 1ll * (x - y + P) * w[j + l] % P;
				f[i + j] = mo(x + y);
			}
}

template <class iter>
void intt(iter f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = 1; l < n; l <<= 1)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				int x = f[i + j];
				int y = 1ll * w[j + l] * f[i + j + l] % P;
				f[i + j] = mo(x + y), f[i + j + l] = mo(x - y + P);
			}
	const int iv = qpow(n);
	for (int i = 0; i < n; i++)
		f[i] = 1ll * f[i] * iv % P;
	reverse(f + 1, f + n);
}

struct Poly : vector<int> { // 大常数板子
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
	friend Poly operator+(const Poly &f, const Poly &g) {
		Poly h = Poly(f).redeg(max(f.deg(), g.deg()));
		for (int i = 0; i < g.deg(); i++)
			h[i] = mo(h[i] + g[i]);
		return h;
	}
	friend Poly operator-(const Poly &f, const Poly &g) {
		Poly h = Poly(f).redeg(max(f.deg(), g.deg()));
		for (int i = 0; i < g.deg(); i++)
			h[i] = mo(h[i] - g[i] + P);
		return h;
	}
	Poly operator*(int k) {
		Poly f = T;
		for (int &fi : f)
			fi = 1ll * fi * k % P;
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
			f[i] = 1ll * f[i] * g[i] % P;
		return f.intt(n);
	}
	friend Poly operator*(Poly f, Poly g) {
		int m = f.deg() + g.deg() - 1;
		return mul(f, g, get_lim(m)).redeg(m);
	}
	Poly deriv() const {
		Poly f(deg() - 1);
		for (int i = 1; i < deg(); i++)
			f[i - 1] = 1ll * i * T[i] % P;
		return f;
	}
	Poly integr() const {
		Poly f(deg() + 1);
		pre_inv(deg() + 1);
		for (int i = deg(); i > 0; --i)
			f[i] = 1ll * Inv[i] * T[i - 1] % P;
		return f;
	}
	Poly inv(int m) const { // 12E
		Poly x = {qpow(T[0])};
		for (int t = 2; t < m * 2; t *= 2) {
			Poly u = cut(t).ntt(t * 2);
			x.ntt(t * 2);
			for (int i = 0; i < t * 2; i++)
				x[i] = (P + 2 - 1ll * u[i] * x[i] % P) * x[i] % P;
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
		return deriv().div(m - 1, cut(m)).integr();
	}
	Poly exp(int m) const { // 48E
		Poly x = {1};
		for (int t = 2; t < m * 2; t *= 2) {
			x = x * (cut(t) - x.ln(t) + Poly{1}), x.redeg(t);
		}
		return x.redeg(m);
	}
	Poly sqrt(int m) const { // 36E
		Poly x = {1};
#ifdef ACM_MATH_CIPOLLA_H
		x[0] = Cipolla(front(), P).first;
#endif
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
	friend Poly operator/(const Poly &f, const Poly &g) {
		int m = f.deg() - g.deg() + 1;
		return f.rev().div(m, g.rev()).rev();
	}
#undef T
};

struct PolyEI {
	std::vector<Poly> p;
	int n, raw_n;
	PolyEI(Poly a) {
		raw_n = a.size(), n = get_lim(raw_n);
		a.redeg(n), p.resize(n * 2);
		for (int i = 0; i < n; i++)
			p[i + n] = {1, P - a[i]};
		for (int i = n - 1; i; i--) {
			int ls = i * 2, rs = i * 2 + 1;
			int len = get_lim(p[ls].size());
			p[ls].ntt(len), p[rs].ntt(len), p[i].redeg(len);
			for (int j = 0; j < len; j++)
				p[i][j] = 1ll * p[ls][j] * p[rs][j] % P;
			p[i].intt(len);
			p[i].push_back(mo(p[i][0] + P - 1)), p[i][0] = 1;
		}
	}
	Poly eval(Poly f) { // PolyEI(x).eval(f)
		int m = f.size();
		if (m == 1)
			return Poly(raw_n, f[0]);
		Poly q = f.rev().div(m, p[1]);
		q.resize(n), rotate(q.begin(), q.begin() + m, q.end());
		for (int k = n, o = 1; k > 1; k >>= 1)
			for (int i = 0; i < n; i += k, o++) {
				if (i >= raw_n)
					continue;
				Poly foo(k), bar(k);
				auto qi = q.begin() + i;
				ntt(qi, k);
				for (int j = 0; j < k; j++) {
					foo[j] = 1ll * qi[j] * p[o * 2 + 1][j] % P;
					bar[j] = 1ll * qi[j] * p[o * 2][j] % P;
				}
				foo.intt(k), bar.intt(k);
				std::copy(foo.begin() + k / 2, foo.end(), qi);
				std::copy(bar.begin() + k / 2, bar.end(), qi + k / 2);
			}
		return q.cut(raw_n);
	}
	Poly inter(const Poly &y) { // PolyEI(x).inter(y)
		Poly q = Poly(p[1]).redeg(raw_n + 1);
		q = eval(q.rev().deriv()).redeg(n);
		for (int i = 0; i < raw_n; i++)
			q[i] = 1ll * y[i] * qpow(q[i]) % P;
		for (int k = 1, h = n / 2; k < n; k *= 2, h >>= 1)
			for (int i = 0, o = h; i < n; i += k * 2, o++) {
				if (i >= raw_n)
					continue;
				auto qi = q.begin() + i;
				Poly foo(qi, qi + k), bar(qi + k, qi + k * 2);
				foo.ntt(k * 2), bar.ntt(k * 2);
				for (int j = 0; j < k * 2; j++) {
					qi[j] = (1ll * foo[j] * p[o * 2 + 1][j] + 1ll * bar[j] * p[o * 2][j]) % P;
				}
				intt(qi, k * 2);
			}
		return q.cut(raw_n).rev();
	}
};

int main() {
    int n, m;
    cin >> n >> m;
    n++;
    Poly f(n), x(m);
    for (int i = 0; i < n; i++)
        cin >> f[i];
    for (int i = 0; i < m; i++)
        cin >> x[i];
    auto g = PolyEI(x).eval(f);
    for (auto v : g)
        printf("%d\n", v);
    return 0;
}

