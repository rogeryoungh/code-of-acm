#include "basic/index.hpp"

#include "basic/modint/modint.hpp"

// @description 拉格朗日插值

Z lagrange(const std::vector<Z> &x, const std::vector<Z> &y, Z k) {
	int n = x.size();
	Z sum = 0;
	for (int i = 0; i < n; i++) {
		Z s1 = 1, s2 = 1;
		for (int j = 0; j < n; j++)
			if (j != i)
				s1 *= k - x[j], s2 *= x[i] - x[j];
		sum += s1 / s2 * y[i];
	}
	return sum;
}
