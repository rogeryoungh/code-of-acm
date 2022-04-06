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
	return 2 << std::__lg(m - 1);
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
#undef T
};

Poly bm(const Poly &a) {
	Poly p = {1}, q = {1};
	int l = 0;
	for (int r = 1; r <= a.deg(); r++) {
		int delta = 0;
		for (int j = 0; j <= l; j++) {
			delta = (delta + 1ll * a[r - 1 - j] * p[j]) % P;
		}
		q.insert(q.begin(), 0);
		if (delta == 0)
			continue;
		Poly t = p;
		if (q.deg() > t.deg()) {
			t.redeg(q.deg());
		}
		for (int i = 0; i < q.deg(); i++) {
			t[i] = mo((t[i] - 1ll * delta * q[i]) % P + P);
		}
		if (2 * l <= r - 1) {
			q = p;
			int od = qpow(delta);
			for (int &x : q) {
				x = 1ll * x * od % P;
			}
			l = r - l;
		}
		swap(p, t);
	}
	assert(p.deg() == l + 1);
	return Poly{1} - p;
}

// [x^n] F/G
int divAt(Poly F, Poly G, ll n) {
	int len = std::max(F.deg(), G.deg()), m = get_lim(len);
	for (; n; n >>= 1) {
		F.ntt(m * 2), G.ntt(m * 2);
		for (int i = 0; i < m * 2; i++)
			F[i] = 1ll * F[i] * G[i ^ 1] % P;
		for (int i = 0; i < m; i++)
			G[i] = 1ll * G[i * 2] * G[i * 2 + 1] % P;
		G.redeg(m);
		F.intt(m * 2), G.intt(m);
		for (int i = 0, j = n & 1; i < len; i++, j += 2)
			F[i] = F[j];
		F.redeg(len), G.redeg(len);
	}
	return F[0];
}

int getAn(Poly F, const Poly &A, ll n) {
	F = Poly{1} - F;
	Poly f = (A * F).cut(A.deg());
	return divAt(f, F, n);
}

int main() {
	int n, m;
	cin >> n >> m;
	Poly p(n);
	for (auto &pi : p)
		cin >> pi;
	auto ret = bm(p);
	for (int i = 1; i < ret.deg(); i++)
		cout << ret[i] << " \n"[i == ret.deg() - 1];
	cout << getAn(ret, p, m);
	return 0;
}
