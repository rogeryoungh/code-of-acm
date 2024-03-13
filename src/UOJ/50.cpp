

// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2022-01-14 00:30:08.423642

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using vi = vector<int>;
using pii = pair<int, int>;

#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
	ll s = 0, w = false, c = getchar();
	for (; !isdigit(c); c = getchar())
		w = w || c == '-';
	for (; isdigit(c); c = getchar())
		s = s * 10 + c - '0';
	return w ? -s : s;
}

// END OF HEADER

#define ACM_MOD 998244353
const int P = ACM_MOD;

#ifdef ACM_MOD
int qpow(ll a, ll b = ACM_MOD - 2, ll m = ACM_MOD) {
#else
int qpow(ll a, ll b, ll m) {
#endif
	ll ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a % m;
		a = a * a % m;
	}
	return ret;
}

template <typename T>
T tpow(T a, ll b) {
	T ret;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a;
		a = a * a;
	}
	return ret;
}

struct m32 {
	int v = 0;
	m32(int _v = 0) {
		v = _v;
	}
	m32 &operator=(const int &m) {
		v = m;
		return *this;
	}
	m32 &operator+=(const m32 &m) {
		v = (v += m.v) >= P ? v - P : v;
		return *this;
	}
	m32 &operator-=(const m32 &m) {
		v = (v -= m.v) < 0 ? v + P : v;
		return *this;
	}
	m32 operator-() const {
		return v == 0 ? 0 : P - v;
	}
	m32 &operator*=(const m32 &m) {
		v = ll(v) * m.v % P;
		return *this;
	}
	m32 operator+(const m32 &m) const {
		return m32(*this) += m;
	}
	m32 operator-(const m32 &m) const {
		return m32(*this) -= m;
	}
	m32 operator*(const m32 &m) const {
		return m32(*this) *= m;
	}
	m32 inv() const {
		return qpow(v);
	}
	m32 pow(int n) const {
		return qpow(v, n, P);
	}
	m32 sqrt() const {
#ifdef ACM_MATH_CIPOLLA_H
		return Cipolla(v, P).first;
#else
		return 1;
#endif
	}
};

inline int get_lim(int n, int s = 1) {
	int m = 1;
	while (m < n)
		m <<= s;
	return m;
}

struct Poly : std::vector<m32> {
	using vector::vector;
	bool isNTT = false;
	int deg() const {
		return size();
	}
	Poly cut(int m, int l = 0) const {
		return Poly(begin() + l, begin() + min(deg(), m + l));
	}
	Poly &resize(int m) {
		vector::resize(m);
		return *this;
	}
	Poly &fillZeroL(int t) {
		fill_n(begin(), t / 2, 0);
		return *this;
	}
	Poly &fillZeroH(int t) {
		fill_n(begin() + t / 2, t / 2, 0);
		return *this;
	}
	friend Poly operator+(Poly f, Poly g);
	friend Poly operator-(Poly f, Poly g);
	friend Poly operator*(Poly f, Poly g);
	Poly &ntt(int m);
	Poly &nttD(int m);
	Poly &intt(int m);
	Poly &invD(Poly f2, Poly nx, int t);
	Poly inv() const;
	Poly div(Poly g) const;
	Poly deriv() const;
	Poly integr() const;
	Poly ln() const;
	Poly exp() const;
	Poly sqrt() const;
	Poly pow(int k) const;
	Poly mod() const;
	Poly rev() const {
		return Poly(rbegin(), rend());
	}
};

Poly w, Inv, fac, ifac;

void pre_w(int n, int w0 = 3) {
	static int lim = (w = {1, 1}, 2);
	n = get_lim(n);
	if (n <= lim)
		return;
	w.resize(n);
	for (int l = lim; l < n; l *= 2) {
		m32 p = m32(w0).pow((P - 1) / l / 2);
		for (int i = 0; i < l; i += 2) {
			w[(l + i)] = w[(l + i) / 2];
			w[l + i + 1] = w[l + i] * p;
		}
	}
	lim = n;
}

void pre_inv(int n) {
	static int LIM = (Inv = {1, 1}, 2);
	if (n <= LIM)
		return;
	Inv.resize(n);
	for (int i = LIM; i < n; i++) {
		Inv[i] = Inv[P % i] * (P - P / i);
	}
	LIM = n;
}

void pre_fac(int lim) {
	fac.resize(lim + 1);
	fac[0] = 1;
	for (int i = 1; i <= lim; i++) {
		fac[i] = fac[i - 1] * i;
	}
}

void pre_ifac(int lim) {
	ifac.resize(lim + 1);
	ifac[lim] = fac[lim].inv();
	for (int i = lim - 1; i >= 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1);
	}
}

static int ntt_size = 0;

void ntt(Poly::iterator f, int deg) {
	pre_w(deg);
	ntt_size += deg;
	for (int l = deg >> 1; l; l >>= 1)
		for (auto fi = f; fi - f < deg; fi += l * 2)
			for (int j = 0; j < l; j++) {
				auto x = fi[j] + fi[j + l];
				fi[j + l] = w[j + l] * (fi[j] - fi[j + l]);
				fi[j] = x;
			}
}

void intt(Poly::iterator f, int deg) {
	ntt_size += deg;
	for (int l = 1; l < deg; l <<= 1)
		for (auto fi = f; fi - f < deg; fi += l * 2)
			for (int j = 0; j < l; j++) {
				auto x = fi[j], y = fi[j + l] * w[j + l];
				fi[j] = x + y, fi[j + l] = x - y;
			}
	const auto deg_inv = P - (P - 1) / deg;
	for (int i = 0; i < deg; i++)
		f[i] *= deg_inv;
	std::reverse(f + 1, f + deg);
}

void nttD(Poly::iterator f, int n) {
	std::copy_n(f, n, f + n);
	intt(f + n, n);
	for (int i = n; i < n * 2; i++)
		f[i] *= w[i];
	ntt(f + n, n);
}

Poly &Poly::ntt(int n) {
	if (!isNTT) {
		resize(n);
		::ntt(begin(), n);
		isNTT = true;
	}
	return *this;
}

Poly &Poly::intt(int m) {
	::intt(begin(), m);
	isNTT = false;
	return *this;
}

Poly &Poly::nttD(int n) {
	resize(n * 2);
	::nttD(begin(), n);
	return *this;
}

Poly &mul(Poly &f, Poly &g, int t) {
	f.ntt(t), g.ntt(t);
	for (int i = 0; i < t; i++)
		f[i] *= g[i];
	return f.intt(t);
}

Poly operator*(Poly f, Poly g) {
	if (f.deg() < g.deg())
		swap(f, g);
	if (g.deg() == 1) {
		for (auto &fi : f)
			fi *= g[0];
		return f;
	}
	int t = f.deg() + g.deg() - 1;
	return mul(f, g, get_lim(t)).cut(t);
}

template <class T>
struct NttCache {
	std::map<T, Poly> maps;
	std::function<Poly(T)> exec;
	Poly &get(T key) {
		Poly &ret = maps[key];
		if (ret.empty())
			ret = exec(key);
		return ret;
	}
};

struct PolyCDQ {
	int now = 0;
	static const int M = 32, B = 16;
	const Poly &F, &G;
	Poly conv;
	NttCache<pii> nr, nf;
	vector<int> U;

	PolyCDQ(const Poly &f, Poly &g) : F(f), G(g) {
		conv.resize(M);
		U.resize(32, -1);
		nf.exec = [&](pii p) {
			return F.cut(p.first, p.second).ntt(p.first);
		};
		nr.exec = [&](pii p) {
			return G.cut(p.first, p.second).ntt(p.first * 2);
		};
	}

	m32 next() { // return sum{i in [0, now)} F[i] G[now - i]
		conv[now] += G[now] * F[0], now++;
		int len = now & -now;
		if (len == now) {
			conv.resize(now * 2);
		}
		if (len < M) {
			for (int j = now & -M; j < now; ++j)
				conv[now] += G[j] * F[now - j];
		} else {
			int u = std::__lg(len / M) / std::__lg(B);
			int t = ++U[u] % (B - 1);
			len = (1 << (u * std::__lg(B))) * M;
			int l = now - len;
			Poly s(len * 2);
			for (int i = 0; i <= t; i++) {
				Poly &a = nr.get({len, l - i * len}), &b = nf.get({len * 2, len * i});
				for (int j = 0; j < len * 2; j++)
					s[j] += a[j] * b[j];
			}
			s.intt(len * 2);
			for (int i = len; i < len * 2; i++)
				conv[l + i] += s[i];
		}
		return conv[now];
	}
};

Poly Poly::inv() const {
	Poly G(deg());
	PolyCDQ X(*this, G);
	m32 iv = front().inv();
	G[0] = iv;
	for (int i = 1; i < deg(); i++)
		G[i] = -X.next() * iv;
	return G;
}

Poly Poly::div(Poly g) const {
	Poly G(deg());
	PolyCDQ X(g.resize(deg()), G);
	m32 iv = g[0].inv();
	G[0] = front() * iv;
	for (int i = 1; i < deg(); i++)
		G[i] = ((*this)[i] - X.next()) * iv;
	return G;
}

// include "template/ntt-mint/oc/0.hpp"

struct PolyOCS {
	int now = 0;
	const int M0 = 1024, M = 32;
	const Poly &F, &G;
	Poly conv;
	NttCache<int> nf, &ng = nf;

	PolyOCS(const Poly &f, const Poly &g) : F(f), G(g) {
		conv.resize(M0);
		nf.exec = [&](int len) {
			return F.cut(len).ntt(len);
		};
		ng.exec = [&](int len) {
			return G.cut(len).ntt(len);
		};
	}

	m32 next() { // return sum{i in [1, now)} F[i] G[now - i]
		conv[now] += G[now] * F[0];
		if (now != 0)
			conv[now] += F[now] * G[0];
		now++;
		int len = now & -now, l = now - len;
		if (now < M0) {
			for (int j = (now & -M0) + 1; j < now; ++j)
				conv[now] += G[j] * F[now - j];
		} else if (len == now) {
			conv.resize(len * 2);
			Poly a = ng.get(len), &b = nf.get(len);
			mul(a, b, len);
			for (int i = len; i < len * 2; i++)
				conv[i] += a[i - len] - conv[i - len];
		} else if (len < M) {
			for (int j = now & -M; j < now; ++j) {
				conv[now] += G[j] * F[now - j] * 2;
			}
		} else {
			Poly a = G.cut(len, l), &b = nf.get(len * 2);
			a.ntt(len * 2);
			for (int i = 0; i < len * 2; ++i)
				a[i] = a[i] * b[i];
			a.intt(len * 2);
			for (int i = len; i < len * 2; i++)
				conv[l + i] += a[i] * 2;
		}
		return conv[now];
	}
};

int main() {
	int n = rr();
	Poly A(n + 2);
	pre_fac(n), pre_ifac(n);
	pre_inv(n + 2);

	const int iv2 = qpow(2);

	for (int i = 0; i < n; i++)
		A[i + 2] = ifac[i] * (getchar() - '0') * iv2;

	// DF = A * G * G + 1, 但 F[0] = 0
	// F = xf => A * f * f - f + 1 = x * df

	// - x * DG = G * G - G + A, G = 1 / f
	Poly G(n);
	PolyOCS X(G, G);
	G[0] = 1;
	for (int i = 1; i < n; i++) {
		G[i] = -(A[i] + X.next()) * Inv[i + 1];
	}

	Poly F = G.inv();

	for (int i = 0; i < n; i++)
		printf("%d\n", (F[i] * fac[i + 1]).v);
	return 0;
}
