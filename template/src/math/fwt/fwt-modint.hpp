#include "basic/index.hpp"

#include "basic/bit.hpp"

#include "basic/modint/modint.hpp"

template <bool inv>
void OR(auto f, int n) {
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++)
				if (inv)
					f[i + j + k] -= f[i + j];
				else
					f[i + j + k] += f[i + j];
}

template <bool inv>
void AND(auto f, int n) {
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++)
				if (inv)
					f[i + j] -= f[i + j + k];
				else
					f[i + j] += f[i + j + k];
}

template <bool inv>
void XOR(auto f, int n) {
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++) {
				Z u = f[i + j], v = f[i + j + k];
				f[i + j] = u + v;
				f[i + j + k] = u - v;
			}
	if (inv) {
		const Z ivn = P - (P - 1) / n;
		for (int i = 0; i < n; i++)
			f[i] *= ivn;
	}
}

auto subset_conv(const std::vector<Z> &f, const std::vector<Z> &g) {
	int N = f.size(), n = std::__lg(f.size());
	std::vector<std::vector<Z>> nf, ng, nr;
	nf = ng = nr = std::vector<std::vector<Z>>(n + 1, std::vector<Z>(N));
	for (int i = 0; i < N; i++)
		nf[popcnt(i)][i] = f[i], ng[popcnt(i)][i] = g[i];
	for (int i = 0; i <= n; i++)
		OR<0>(nf[i].begin(), N), OR<0>(ng[i], N);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n - i; j++)
			for (int k = 0; k < N; k++)
				nr[i + j][k] += nf[i][k] * ng[j][k];
	for (int i = 0; i <= n; i++)
		OR<1>(nr[i], N);
	std::vector<Z> r(N);
	for (int i = 0; i < N; i++)
		r[i] = nr[popcnt(i)][i];
	return r;
}
