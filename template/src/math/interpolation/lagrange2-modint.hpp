#include "basic/index.hpp"

#include "basic/modint/modint.hpp"

// @description 拉格朗日插值

auto lagrange(const V<Z> &x, const V<Z> &y) {
	int n = x.size();
	V<Z> d(n), u(n + 1), t(n);
	u[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j >= 1; j--)
			u[j] = u[j - 1] - u[j] * x[i];
		u[0] *= -x[i];
	}
	for (int i = 0; i < n; i++) {
		Z s2 = 1;
		for (int j = n; j >= 1; j--) {
			t[j - 1] = j == n ? u[n] : u[j] + x[i] * t[j];
			if (j - 1 != i)
				s2 = s2 * (x[i] - x[j - 1]);
		}
		s2 = s2.inv();
		for (int j = 0; j < n; j++)
			d[j] += t[j] * s2 * y[i];
	}
	return d;
}
