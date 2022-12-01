#include "basic/index.hpp"

#include "basic/bit.hpp"

#include "basic/qpow/qpow-P.hpp"

void OR(V<int> &f, bool inv) {
	int n = f.size(), x = inv ? 1 : P - 1;
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++)
				f[i + j + k] = (f[i + j + k] + 1ll * f[i + j] * x) % P;
}

void AND(V<int> &f, bool inv) {
	int n = f.size(), x = inv ? 1 : P - 1;
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++)
				f[i + j] = (f[i + j] + 1ll * f[i + j + k] * x) % P;
}

void XOR(V<int> &f, bool inv) {
	int n = f.size(), x = inv ? 1 : qpow(2);
	for (int k = 1; k < n; k <<= 1)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++) {
				int u = f[i + j], v = f[i + j + k];
				f[i + j] = 1ll * (u + v) * x % P;
				f[i + j + k] = 1ll * (u - v + P) * x % P;
			}
}

auto subset_conv(const V<int> &f, const V<int> &g) {
	int N = f.size(), n = std::__lg(f.size());
	V<V<int>> nf, ng, nr;
	nf = ng = nr = V<V<int>>(n + 1, V<int>(N));
	for (int i = 0; i < N; i++)
		nf[popcnt(i)][i] = f[i], ng[popcnt(i)][i] = g[i];
	for (int i = 0; i <= n; i++)
		OR(nf[i], true), OR(ng[i], true);
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= n - j; k++)
				nr[j + k][i] = (nr[j + k][i] + 1ll * nf[j][i] * ng[k][i]) % P;
	for (int i = 0; i <= n; i++)
		OR(nr[i], false);
	V<int> r(N);
	for (int i = 0; i < N; i++)
		r[i] = nr[popcnt(i)][i];
	return r;
}
