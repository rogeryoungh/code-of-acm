#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using u64 = std::uint64_t;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

namespace Mker {
u64 SA, SB, SC;
void init() {
	cin >> SA >> SB >> SC;
}
u64 rand() {
	SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
	u64 t = SA;
	SA = SB, SB = SC, SC ^= t ^ SA;
	return SC;
}
}; // namespace Mker

const int P = 1E9 + 7;

int qpow(int a, int b = P - 2, int m = P) {
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

struct FP2 {
	inline static int P, I;
	int a = 1, b = 0; // a+bi, i^2=a^2-n
	friend FP2 operator*(FP2 i1, FP2 i2) {
		int x = (1ll * i1.a * i2.a + 1ll * i1.b * i2.b % P * I) % P;
		int y = (1ll * i1.b * i2.a + 1ll * i1.a * i2.b) % P;
		return FP2{x, y};
	}
};

// a[n] = A a[n-1] + B a[n-2] | a[0] = 0, a[1] = 1
template <int U = 1 << 16>
struct AP_F2 {
	FP2 f1[U], f2[U], f3[U], f4[U];
	int Det, SDet, ivS, SivS;

	void pre_qpow(FP2 *f, FP2 q) {
		f[0] = {1, 0}, f[1] = q;
		for (int i = 2; i < U; i++) {
			f[i] = f[i - 1] * q;
		}
	}
	AP_F2(int A, int B) {
		FP2::P = P, FP2::I = (1ll * A * A + 4ll * B) % P;
		int qq1 = 1ll * A * qpow(2) % P;
		FP2 q1 = {qq1, qpow(2)};

		pre_qpow(f1, q1);
		pre_qpow(f2, f1[U - 1] * q1);
	}
	int get(u64 n) {
		n = n % (P - 1);
		auto &i1 = f1[n % U], &i2 = f2[n / U];
		return (2ll * i1.b * i2.a + 2ll * i1.a * i2.b) % P;
	}
};

int main() {
	AP_F2<> ap(233, 666);
	int T;
	cin >> T;
	Mker::init();
	int ret = 0;
	while (T--) {
		ret ^= ap.get(Mker::rand());
	}
	cout << ret;
	return 0;
}
