#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int qpow(int a, int b, int m) {
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

template <typename T>
T tpow(T a, ll b) {
	T ret;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a;
		a = a * a;
	}
	return ret;
}

ll legendre(ll a, ll p) {
	return qpow(a, (p - 1) / 2, p);
}

struct FP2 {
	inline static ll P, I;
	ll a = 1, b = 0; // a+bi, i^2=a^2-n
	friend FP2 operator*(FP2 i1, FP2 i2) {
		return FP2{(i1.a * i2.a + i1.b * i2.b % P * I) % P, (i1.b * i2.a + i1.a * i2.b) % P};
	}
};

ll cipolla(ll n, ll p) {
	FP2::P = p;
	if (n % p == 0)
		return 0;
	if (legendre(n, p) != 1)
		return -1;

	ll a = -1;
	for (a = 0; a < p; a++) {
		ll i = (a * a - n + p) % p;
		if (legendre(i, p) == p - 1) {
			FP2::I = i;
			break;
		}
	}
	ll ans = tpow(FP2{a, 1}, (p + 1) / 2).a;
	return min(ans, p - ans);
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		ll n, p;
		cin >> n >> p;
		auto ans = cipolla(n, p);
		if (ans == -1)
			cout << "Hola!\n";
		else if (ans == 0 || ans == p - ans)
			cout << ans << "\n";
		else
			cout << ans << " " << p - ans << "\n";
	}
	return 0;
}
