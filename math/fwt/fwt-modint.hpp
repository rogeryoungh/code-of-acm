#include "basic/index.hpp"

#include "basic/bit.hpp"

#include "basic/modint/modint.hpp"

void OR(V<Z> &f, bool inv) {
	int n = f.size(), x = inv ? 1 : -1;
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++)
				f[i + j + k] += f[i + j] * x;
}

void AND(V<Z> &f, bool inv) {
	int n = f.size(), x = inv ? 1 : -1;
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++)
				f[i + j] += f[i + j + k] * x;
}

void XOR(V<Z> &f, bool inv) {
	int n = f.size(), x = inv ? 1 : qpow(2);
	for (int k = 1; k < n; k <<= 1)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++) {
				Z u = f[i + j], v = f[i + j + k];
				f[i + j] = (u + v) * x;
				f[i + j + k] = (u - v) * x;
			}
}

auto subset_conv(const V<Z> &f, const V<Z> &g) {
	int N = f.size(), n = std::__lg(f.size());
	V<V<Z>> nf, ng, nr;
	nf = ng = nr = V<V<Z>>(n + 1, V<Z>(N));
	for (int i = 0; i < N; i++)
		nf[popcnt(i)][i] = f[i], ng[popcnt(i)][i] = g[i];
	for (int i = 0; i <= n; i++)
		OR(nf[i], true), OR(ng[i], true);
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= n - j; k++)
				nr[j + k][i] += nf[j][i] * ng[k][i];
	for (int i = 0; i <= n; i++)
		OR(nr[i], false);
	V<Z> r(N);
	for (int i = 0; i < N; i++)
		r[i] = nr[popcnt(i)][i];
	return r;
}
