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

int sqrt_mod(int n, int p) {
	for (int i = 0; i < p; i++)
		if (1ll * i * i % p == n)
			return i;
	return -1;
}

// a[n] = A a[n-1] + B a[n-2]
template <int U = 1 << 16>
struct AP_F1 {
	int f1[U], f2[U], f3[U], f4[U];
	int Det, SDet, ivS, SivS;

	void pre_qpow(int *f, int q) {
		f[0] = 1, f[1] = q;
		for (int i = 2; i < U; i++) {
			f[i] = 1ll * f[i - 1] * q % P;
		}
		for (int i = 0; i < U; i++) {
			f[i] = 1ll * f[i] * SivS % P;
		}
	}
	AP_F1(int A, int B) {
		Det = (1ll * A * A + 4ll * B) % P;
		SDet = 188305837; // sqrt_mod(Det, P);
		ivS = qpow(SDet);
		SivS = 308857161; // sqrt_mod(ivS, P);
		assert(SDet != -1), assert(SivS != -1);
		cerr << SDet << "\n";
		cerr << SivS << "\n";

		int q1 = 1ll * (A + SDet) * qpow(2) % P;
		int q2 = 1ll * (A - SDet + P) * qpow(2) % P;
		pre_qpow(f1, q1);
		pre_qpow(f3, q2);
		pre_qpow(f2, qpow(q1, U));
		pre_qpow(f4, qpow(q2, U));
	}
	int get(u64 n) {
		n = n % (P - 1);
		ll ans = 1ll * f1[n % U] * f2[n / U];
		ans -= 1ll * f3[n % U] * f4[n / U];
		ans = ans % P;
		return ans < 0 ? ans + P : ans;
	}
};

int main() {
	AP_F1<> ap(233, 666);
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
