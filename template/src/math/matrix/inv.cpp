#include "basic/index.hpp"

#include "math/matrix/gauss-modint.cpp"

std::optional<VV<Z>> matrix_inv(const VV<Z> &v) {
	assert(v.x == v.y);
	int n = v.x;
	VV<Z> v2(n, n * 2);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			v2[i][j] = v[i][j];
		}
		v2[i][i + n] = 1;
	}
	auto ret = gauss(v2);
	if (!ret.has_value()) {
		return std::nullopt;
	} else {
		const auto &g = ret.value();
		VV<Z> r(n, n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				r[i][j] = g[i][j + n];
		return r;
	}
}
