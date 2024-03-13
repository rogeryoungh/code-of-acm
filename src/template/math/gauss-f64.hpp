#pragma once
#include "../base.hpp"
#include "../base/vec2d.hpp"

// #region snippet
std::optional<vec2d<f64>> gauss(vec2d<f64> v, f64 eps = 1E-6) {
	for (int i = 0; i < v.x; i++) {
		int mi = i;
		for (int j = i + 1; j < v.x; j++)
			if (std::abs(v[j][i]) > std::abs(v[mi][i]))
				mi = j;
		for (int j = 0; j < v.y; j++)
			std::swap(v[i][j], v[mi][j]);
		if (std::abs(v[i][i]) < eps)
			return std::nullopt;
		auto ivi = 1 / v[i][i];
		for (int k = v.y - 1; k >= i; k--)
			v[i][k] *= ivi;
		for (int j = 0; j < v.x; j++) {
			if (j != i) {
				auto tmp = v[j][i];
				for (int k = 0; k < v.y; k++)
					v[j][k] -= v[i][k] * tmp;
			}
		}
	}
	return v;
}
// #endregion snippet
