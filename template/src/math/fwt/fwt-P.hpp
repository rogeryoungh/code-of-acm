#include "basic/index.hpp"

#include "basic/bit.hpp"

#include "basic/qpow/qpow-P.hpp"

template <bool inv>
void OR(auto f, int n) {
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++)
				if (inv)
					f[i + j + k] = mo(f[i + j + k] - f[i + j] + P);
				else
					f[i + j + k] = mo(f[i + j + k] + f[i + j]);
}

template <bool inv>
void AND(auto f, int n) {
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++)
				if (inv)
					f[i + j] = mo(f[i + j] - f[i + j + k] + P);
				else
					f[i + j] = mo(f[i + j] + f[i + j + k]);
}

template <bool inv>
void XOR(auto f, int n) {
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++) {
				int u = f[i + j], v = f[i + j + k];
				f[i + j] = mo(u + v);
				f[i + j + k] = mo(u - v + P);
			}
	if (inv) {
		const int ivn = P - (P - 1) / n;
		for (int i = 0; i < n; i++)
			f[i] = 1ll * f[i] * ivn % P;
	}
}

auto subset_conv(const V<int> &f, const V<int> &g) {
	int N = f.size(), n = std::__lg(f.size());
	V<V<int>> nf, ng, nr;
	nf = ng = nr = V<V<int>>(n + 1, V<int>(N));
	for (int i = 0; i < N; i++)
		nf[popcnt(i)][i] = f[i], ng[popcnt(i)][i] = g[i];
	for (int i = 0; i <= n; i++)
		OR<0>(nf[i].begin(), N), OR<0>(ng[i].begin(), N);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n - i; j++)
			for (int k = 0; k < N; k++)
				nr[i + j][k] = (nr[i + j][k] + 1ll * nf[i][k] * ng[j][k]) % P;
	for (int i = 0; i <= n; i++)
		OR<1>(nr[i].begin(), N);
	V<int> r(N);
	for (int i = 0; i < N; i++)
		r[i] = nr[popcnt(i)][i];
	return r;
}
