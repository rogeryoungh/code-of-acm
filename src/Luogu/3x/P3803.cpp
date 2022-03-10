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
	int n, m;
	cin >> n >> m;
	n++, m++;
	Poly f(n), g(m);
	for (auto &fi : f)
		cin >> fi;
	for (auto &gi : g)
		cin >> gi;
	auto ans = f * g;
	for (auto &ai : ans)
		cout << ai << " ";
	return 0;
}
