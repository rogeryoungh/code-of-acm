// Author: Roger Young
// Date: 2022-02-07 20:51:37.740141

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define _dbg(...) 1
#define dbg(x) 1

#define getchar getchar_unlocked
#define putchar putchar_unlocked

struct buf {
	char a[1 << 26], *s, *t;
	buf() : s(a), t(a) {
		a[fread(a, 1, sizeof a, stdin)] = 0;
	}
	~buf() {
		fwrite(a, 1, t - a, stdout);
	}
	operator uint() {
		int x = 0;

		while (*s > 47)
			x = x * 10 + *s++ - 48;

		++s;
		return x;
	}
	void out(uint n) {
#define pyo(x) *t++ = x

		switch (n) {
		case 1000000000 ... 2147483647:
			pyo(48 + n / 1000000000);
			n %= 1000000000;

		case 100000000 ... 999999999:
			pyo(48 + n / 100000000);
			n %= 100000000;

		case 10000000 ... 99999999:
			pyo(48 + n / 10000000);
			n %= 10000000;

		case 1000000 ... 9999999:
			pyo(48 + n / 1000000);
			n %= 1000000;

		case 100000 ... 999999:
			pyo(48 + n / 100000);
			n %= 100000;

		case 10000 ... 99999:
			pyo(48 + n / 10000);
			n %= 10000;

		case 1000 ... 9999:
			pyo(48 + n / 1000);
			n %= 1000;

		case 100 ... 999:
			pyo(48 + n / 100);
			n %= 100;

		case 10 ... 99:
			pyo(48 + n / 10);
			n %= 10;
		}

		pyo(48 + n);
		pyo(' ');
	}
} it;

// END OF HEADER

#define ACM_MOD 998244353
const int P = ACM_MOD;

#define ACM_MATH_CIPOLLA_H

#ifdef ACM_MOD
int qpow(int a, int b = P - 2, int m = P) {
#else
int qpow(int a, int b, int m) {
#endif
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
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

namespace Qresidue {
ll legendre(ll a, ll p) {
	return qpow(a, (p - 1) / 2, p);
}

ll find_a(ll n, ll p) {
	for (ll a = 0; a < p; a++) {
		ll i = (a * a - n + p) % p;
		if (qpow(i, (p - 1) / 2, p) == p - 1)
			return a;
	}
	return -1;
}

ll P, I;
struct expnum {
	ll a = 1, b = 0;
};
expnum operator*(expnum i1, expnum i2) {
	return expnum{(i1.a * i2.a + i1.b * i2.b % P * I) % P, (i1.b * i2.a + i1.a * i2.b) % P};
}

std::pair<int, int> Cipolla(ll n, ll _p) {
	P = _p;
	if (n % P == 0) // 不互质的情形
		return {0, 0};
	if (legendre(n, P) != 1)
		return {-1, -1}; // 返回-1表示无解
	ll a = find_a(n, P);
	I = (a * a - n + P) % P;
	ll ans = tpow(expnum{a, 1}, (P + 1) / 2).a % P;
	if (2 * ans > P)
		ans = P - ans;
	return {ans, P - ans};
}
}; // namespace Qresidue

std::pair<int, int> Cipolla(ll n, ll p) {
	return Qresidue::Cipolla(n, p);
}

//#include "template/basic/mint/fm.hpp"

#define OPERATOR(T, op)               \
	T operator op(const T &o) const { \
		return T(*this) op## = o;     \
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
	OPERATOR(m32, +)
	OPERATOR(m32, -)
	OPERATOR(m32, *)
	m32 pow(int n) const {
		return qpow(v, n, P);
	}
	m32 inv() const {
		return pow(P - 2);
	}
	m32 sqrt() const {
#ifdef ACM_MATH_CIPOLLA_H
		return Cipolla(v, P).first;
#else
		return 1;
#endif
	}
};

vector<m32> w, Inv, fac, ifac;

inline int get_lim(int n, int s = 1) {
	int m = 1;
	while (m < n)
		m <<= s;
	return m;
}

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

static int ntt_size = 0;
static u64 uu[1 << 18];

template <class iter>
void ntt(iter f, int n) {
	pre_w(n), ntt_size += n;
	for (int i = 0; i < n; i++)
		uu[i] = f[i].v;
	for (int l = n >> 1; l; l >>= 1)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				auto x = uu[i + j] + uu[i + j + l];
				if (x >= P)
					x -= P;
				uu[i + j + l] = (uu[i + j] - uu[i + j + l] + P) * w[j + l].v % P;
				uu[i + j] = x;
			}
	for (int i = 0; i < n; i++)
		f[i] = uu[i] % P;
}

template <class iter>
void intt(iter f, int n) {
	ntt_size += n;
	for (int i = 0; i < n; i++)
		uu[i] = f[i].v;
	for (int l = 1; l < n; l <<= 1)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				auto x = uu[i + j], y = uu[i + j + l] * w[j + l].v % P;
				uu[i + j] = x + y, uu[i + j + l] = x - y + P;
			}
	const auto iv = P - (P - 1) / n;
	for (int i = 0; i < n; i++)
		f[i] = uu[i] * iv % P;
	std::reverse(f + 1, f + n);
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
	Poly &redeg(int m) {
		return resize(m), *this;
	}
	Poly &fillZeroL(int t) {
		return fill_n(begin(), t / 2, 0), *this;
	}
	Poly &fillZeroH(int t) {
		return fill_n(begin() + t / 2, t / 2, 0), *this;
	}
	Poly &ntt(int n) {
		if (!isNTT) {
			::ntt(redeg(n).begin(), n);
			isNTT = true;
		}
		return *this;
	}
	Poly &intt(int n) {
		::intt(begin(), n);
		isNTT = false;
		return *this;
	}
	Poly &nttD(int n);
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
	return mul(f, g, get_lim(t)).redeg(t);
}

Poly &Poly::invD(Poly f2, Poly nx, int t) {
	mul(f2, nx, t).fillZeroL(t); // 6E
	mul(f2, nx, t);				 // 4E
	resize(t);
	for (int i = t / 2; i < t; i++)
		(*this)[i] = -f2[i];
	return *this;
}

Poly Poly::inv() const { // 10E
	Poly x = {front().inv()};
	if (deg() == 1)
		return x;
	for (int t = 2; t < deg() * 2; t <<= 1)
		x.invD(cut(t), x, t);
	return x.cut(deg());
}

Poly Poly::div(Poly f2) const { // 13E
	if (deg() == 1)
		return {front() * f2[0].inv()};
	int t = get_lim(deg());
	Poly x = cut(t / 2), g = Poly(f2).redeg(t / 2).inv(); // 10E
	Poly q = mul(x, g, t).cut(t / 2);					  // 6E
	mul(q, f2, t).fillZeroL(t);							  // 6E
	for (int i = t / 2; i < std::min(t, deg()); i++)
		q[i] -= (*this)[i];
	mul(q, g, t); // 4E
	for (int i = t / 2; i < t; i++)
		x[i] = -q[i];
	return x.cut(deg());
}

Poly Poly::sqrt() const {
	if (deg() == 1) {
		return {front().sqrt()};
	}
	const int R = 16, iv2 = qpow(2);
	int m = get_lim((deg() - 1) / R + 1);
	Poly x = cut(m).sqrt(), h = x.inv().ntt(m * 2);
	vector<Poly> ng(R);

	for (int k = 1; x.deg() < deg(); k++) {
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
		psi.intt(m * 2).fillZeroH(m * 2);
		for (int j = 0; j < min(m, deg() - m * k); j++)
			psi[j] += (*this)[m * k + j];
		mul(psi, h, m * 2);
		x.redeg((k + 1) * m);
		for (int i = 0; i < m; i++)
			x[m * k + i] = psi[i] * iv2;
	}
	return x.cut(deg());
}

Poly yosupo_sqrt(const Poly &x) {
	int pos = 0;
	while (pos < x.deg() && x[pos].v == 0) {
		pos++;
	}
	if (pos == x.deg()) {
		return Poly(x.deg(), 0);
	} else if (pos % 2 == 1 || x[pos].pow(P / 2).v != 1) {
		return {};
	}
	Poly u = {x.begin() + pos, x.end()};
	u = u.redeg(u.deg() + pos / 2).sqrt();
	u.insert(u.begin(), pos / 2, 0);
	return u;
}

int main() {
	int n = it;
	Poly f(n);
	for (int i = 0; i < n; i++)
		f[i] = it;
	Poly ans = yosupo_sqrt(f);
	// cerr << ntt_size << endl;
	if (ans.empty()) {
		puts("-1");
	} else {
		for (int i = 0; i < n; i++)
			it.out(ans[i].v);
	}
	return 0;
}
