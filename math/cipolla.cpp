#include <algorithm>
using ll = long long;
using namespace std;

// @problem https://www.luogu.com.cn/problem/P5491

// @description 快速幂(i32)

int qpow(int a, int b, int m) {
	int ret = m != 1;
	for (; b > 0; b /= 2) {
		if (b % 2 == 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

// @description 二次剩余(cipolla)

template <class T>
T tpow(T a, ll b) {
	T ret;
	for (; b; b /= 2) {
		if (b % 2 == 1)
			ret = ret * a;
		a = a * a;
	}
	return ret;
}

struct FP2 {
	inline static ll P, I;
	ll a = 1, b = 0; // a+bi, i^2=a^2-n
	friend FP2 operator*(FP2 i1, FP2 i2) {
		return FP2{(i1.a * i2.a + i1.b * i2.b % P * I) % P, (i1.b * i2.a + i1.a * i2.b) % P};
	}
};

ll legendre(ll a, ll p) {
	return qpow(a, (p - 1) / 2, p);
}

ll cipolla(ll n, ll p) {
	if (n % p == 0)
		return 0;
	if (legendre(n, p) != 1)
		return -1;
	ll a = -1;
	for (a = 0; a < p; a++) {
		ll i = (a * a - n + p) % p;
		if (legendre(i, p) == p - 1) {
			FP2::P = p, FP2::I = i;
			break;
		}
	}
	ll ans = tpow(FP2{a, 1}, (p + 1) / 2).a;
	return min(ans, p - ans);
}