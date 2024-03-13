#pragma once
#include "../base.hpp"
#include "../base/vec2d.hpp"

// #region snippet
template <class Z>
std::optional<vec2d<Z>> gauss(vec2d<Z> v) {
	for (int i = 0; i < v.x; i++) {
		int mi = i;
		for (int j = i + 1; j < v.x; j++)
			if (v[j][i].v != 0)
				mi = j;
		for (int j = 0; j < v.y; j++)
			std::swap(v[i][j], v[mi][j]);
		if (v[i][i].v == 0)
			return std::nullopt;
		auto ivi = v[i][i].inv();
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
