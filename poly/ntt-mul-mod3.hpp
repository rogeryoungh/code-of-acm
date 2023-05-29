#include "basic/index.hpp"

#include "basic/qpow/qpow.hpp"

// @description 多项式乘法(int mod)

using Poly = std::vector<int>;

inline int get_lim(int m) {
	return 1 << std::__lg(m * 2 - 1);
}

template <int P>
struct NTT {
	inline static Poly w{1, 1};

	inline static int ntt_size = 0;

	static inline int mo(int u) {
		return u >= P ? u - P : u;
	}

	static void pre_w(int n) {
		int l = w.size(), l2 = l * 2;
		if (n <= l)
			return;
		w.resize(l2);
		int p = qpow(3, (P - 1) / l2, P);
		for (int i = l; i < l2; i += 2) {
			w[i] = w[i / 2];
			w[i + 1] = 1ll * w[i] * p % P;
		}
		pre_w(n);
	}

	static void ntt(auto f, int n) {
		pre_w(n), ntt_size += n;
		for (int l = n / 2; l; l /= 2)
			for (int i = 0; i < n; i += l * 2)
				for (int j = 0; j < l; j++) {
					int x = f[i + j], y = f[i + j + l];
					f[i + j + l] = 1ll * (x - y + P) * w[j + l] % P;
					f[i + j] = mo(x + y);
				}
	}

	static void intt(auto f, int n) {
		pre_w(n), ntt_size += n;
		for (int l = 1; l < n; l *= 2)
			for (int i = 0; i < n; i += l * 2)
				for (int j = 0; j < l; j++) {
					int x = f[i + j];
					int y = 1ll * w[j + l] * f[i + j + l] % P;
					f[i + j] = mo(x + y), f[i + j + l] = mo(x - y + P);
				}
		const int ivn = P - (P - 1) / n;
		for (int i = 0; i < n; i++)
			f[i] = 1ll * f[i] * ivn % P;
		std::reverse(f + 1, f + n);
	};
};

template <int P>
Poly mul(Poly &f, Poly g, int n) {
	for (int i = 0; i < n; i++)
		f[i] %= P, g[i] %= P;
	NTT<P>::ntt(f.begin(), n), NTT<P>::ntt(g.begin(), n);
	for (int i = 0; i < n; i++)
		f[i] = 1ll * f[i] * g[i] % P;
	return NTT<P>::intt(f.begin(), n), f;
}

Poly mul3(Poly f, Poly g, int p) {
	constexpr std::array<int, 3> M = {985661441, 998244353, 1004535809};
	int m = f.size() + g.size() - 1, N = get_lim(m);
	f.resize(N), g.resize(N);

	std::array<Poly, 3> a = {f, f, f};
	mul<M[0]>(a[0], g, N);
	mul<M[1]>(a[1], g, N);
	mul<M[2]>(a[2], g, N);

	Poly ans(m);

	const ll M12 = ll(M[0]) * M[1] % p;
	const ll inv_1 = qpow(M[0], M[1] - 2, M[1]);
	const ll inv_2 = qpow(ll(M[0]) * M[1] % M[2], M[2] - 2, M[2]);

	for (int i = 0; i < m; i++) {
		ll x = (a[1][i] - a[0][i] + M[1]) * inv_1 % M[1] * M[0] + a[0][i];
		ans[i] = ((a[2][i] - x % M[2] + M[2]) * inv_2 % M[2] * M12 + x) % p;
	}
	return ans;
}
