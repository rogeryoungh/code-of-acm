#include "basic/index.hpp"

#include "basic/vec2.cpp"

const double eps = 1E-6;

auto Gauss(VV<double> v) {
	assert(v.x == v.y - 1);
	int n = v.x;
	for (int i = 0; i < n; i++) {
		int mi = i;
		for (int j = i + 1; j < n; j++)
			if (std::abs(v[j][i]) > std::abs(v[mi][i]))
				mi = j;
		for (int j = 0; j < n + 1; j++)
			std::swap(v[i][j], v[mi][j]);
		if (std::abs(v[i][i]) < eps)
			return VV<double>(0, 0);
		for (int j = 0; j < n; j++) {
			if (j != i) {
				double tmp = v[j][i] / v[i][i];
				for (int k = i + 1; k < n + 1; k++)
					v[j][k] -= v[i][k] * tmp;
			}
		}
	}
	return v;
}
