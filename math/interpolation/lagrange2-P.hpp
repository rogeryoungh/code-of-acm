#include "basic/index.hpp"

#include "basic/qpow/qpow-P.hpp"

// @description 拉格朗日插值

auto lagrange(const std::vector<int> &x, const std::vector<int> &y) {
	int n = x.size();
	std::vector<int> d(n), u(n + 1), t(n);
	u[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j >= 1; j--)
			u[j] = (u[j - 1] + 1ll * (P - u[j]) * x[i]) % P;
		u[0] = 1ll * u[0] * (P - x[i]) % P;
	}
	for (int i = 0; i < n; i++) {
		int s2 = 1;
		for (int j = n; j >= 1; j--) {
			t[j - 1] = j == n ? u[n] : (u[j] + 1ll * x[i] * t[j]) % P;
			if (j - 1 != i)
				s2 = 1ll * s2 * (x[i] - x[j - 1] + P) % P;
		}
		s2 = qpow(s2);
		for (int j = 0; j < n; j++)
			d[j] = (d[j] + 1ll * t[j] * s2 % P * y[i]) % P;
	}
	return d;
}
