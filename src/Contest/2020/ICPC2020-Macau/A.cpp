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

using Poly = vector<int>;
std::vector<int> w{1, 1}, Inv{1, 1}, fac, ifac;

inline int get_lim(int m) {
	return 2 << std::__lg(m - 1);
}

inline int mo(int u) {
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

void pre_fac(int n) {
	fac.resize(n), ifac.resize(n);
	fac[0] = 1;
	for (int i = 1; i < n; i++) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
}

void pre_ifac(int n) {
	ifac.resize(n);
	ifac[0] = 1;
	ifac[n - 1] = qpow(fac[n - 1]);
	for (int i = n - 2; i > 0; i--) {
		ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
	}
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

using Poly = vector<int>;

Poly &mul(Poly &f, Poly &g, int n) {
	f.resize(n), g.resize(n);
	ntt(f.begin(), n), ntt(g.begin(), n);
	for (int i = 0; i < n; i++)
		f[i] = 1ll * f[i] * g[i] % P;
	intt(f.begin(), n);
	return f;
}

Poly operator*(Poly f, Poly g) {
	int m = f.size() + g.size() - 1;
	mul(f, g, get_lim(m));
	return f.resize(m), f;
}

int main() {
	int T;
	cin >> T;
	pre_fac(1e5 + 10);
	while (T--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (int i = 0; i < n; i++)
			cin >> a[i];

		std::function<Poly(int, int)> solve = [&](int l, int r) {
			if (l == r)
				return Poly{1, a[l]};
			int mid = (l + r) / 2;
			auto p1 = solve(l, mid), p2 = solve(mid + 1, r);
			return p1 * p2;
		};

		auto ret = solve(0, n - 1);
		ll ans = 0;
		for (int i = 1; i <= n; i++)
			ans += 1ll * ret[i] * fac[i] % P * fac[n - i] % P;
		printf("%lld\n", ans % P * qpow(fac[n]) % P);
	}
	return 0;
}
