#include "basic/index.hpp"

#include "math-P/qpow.hpp"

// @description 拉格朗日插值

int lagrange(const V<int> &x, const V<int> &y, int k) {
	int sum = 0, n = x.size();
	for (int i = 0; i < n; i++) {
		int s1 = 1, s2 = 1;
		for (int j = 0; j < n; j++) {
			if (j == i)
				continue;
			s1 = 1ll * s1 * (k - x[j] + P) % P;
			s2 = 1ll * s2 * (x[i] - x[j] + P) % P;
		}
		sum += 1ll * s1 * qpow(s2) % P * y[i] % P;
	}
	return sum % P;
}
