#include "basic/index.hpp"

#include "math-modint/basic.hpp"

// @description 拉格朗日插值

Z lagrange(const V<Z> &y, int x) {
	int n = y.size();
	if (0 <= x && x < n)
		return y[x];
	V<Z> pl(n + 2, 1), pr(n + 2, 1), fac(n + 2, 1);
	for (int i = 0; i < n; i++)
		pl[i + 1] = pl[i] * (x - i);
	for (int i = n - 1; i >= 0; i--)
		pr[i] = pr[i + 1] * (x - i);
	for (int i = 1; i < n; i++)
		fac[i] = fac[i - 1] * i;
	Z ans = 0;
	for (int i = 0; i < n; i++) {
		Z s1 = pl[i] * pr[i + 1];
		Z t = (n - i) % 2 == 0 ? -1 : 1;
		Z s2 = fac[i] * fac[n - i - 1] * t;
		ans += s1 / s2 * y[i];
	}
	return ans;
}
