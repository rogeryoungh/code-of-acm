#include "basic/index.hpp"

#include "basic/qpow/qpow-P.hpp"

// @description 拉格朗日插值

int lagrange(const std::vector<int> &y, int x) {
	int n = y.size();
	if (0 <= x && x < n)
		return y[x];
	std::vector<int> pl(n + 2, 1), pr(n + 2, 1), fac(n + 2, 1);
	for (int i = 0; i < n; i++)
		pl[i + 1] = 1ll * pl[i] * (x - i) % P;
	for (int i = n - 1; i >= 0; i--)
		pr[i] = 1ll * pr[i + 1] * (x - i) % P;
	for (int i = 1; i < n; i++)
		fac[i] = 1ll * fac[i - 1] * i % P;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int s1 = 1ll * pl[i] * pr[i + 1] % P;
		int t = (n - i) % 2 == 0 ? P - 1 : 1;
		int s2 = 1ll * fac[i] * fac[n - i - 1] % P * t % P;
		ans = (ans + 1ll * s1 % P * qpow(s2) % P * y[i]) % P;
	}
	return ans;
}
