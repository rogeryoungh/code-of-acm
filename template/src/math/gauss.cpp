#include "basic/index.hpp"

#include "basic/vec2.cpp"

const double eps = 1E-6;

template <class T>
std::optional<VV<T>> Gauss(VV<T> v) {
	for (int i = 0; i < v.x; i++) {
		int mi = i;
		for (int j = i + 1; j < v.x; j++)
			if (std::abs(v[j][i]) > std::abs(v[mi][i]))
				mi = j;
		for (int j = 0; j < v.y; j++)
			std::swap(v[i][j], v[mi][j]);
		if (std::abs(v[i][i]) < eps)
			return std::nullopt;
		for (int j = 0; j < v.x; j++) {
			if (j != i) {
				auto tmp = v[j][i] / v[i][i];
				for (int k = 0; k < v.y; k++)
					v[j][k] -= v[i][k] * tmp;
			}
		}
	}
	return v;
}
