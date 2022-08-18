#include <vector>
using ll = long long;
using namespace std;

const int P = 998244353;

// @problem https://www.luogu.com.cn/problem/P4781

// @description 快速幂(i32, P)

int qpow(int a, int b = P - 2, int m = P) {
	int ret = m != 1;
	for (; b > 0; b /= 2) {
		if (b % 2 == 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

// @description 拉格朗日插值

ll lagrange(const vector<ll> &x, const vector<ll> &y, ll k) {
	ll sum = 0, n = x.size();
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
