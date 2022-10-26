#include "basic/index.hpp"

#include "basic/qpow.cpp"

// @description 多项式乘法(int mod)

using Poly = std::vector<int>;

inline int get_lim(int m) {
	return 2 << std::__lg(m - (m > 1));
}

template <int P>
struct NTT {
	inline static Poly w{1, 1};

	inline static int ntt_size = 0;

	static inline int mo(int u) {
		return u >= P ? u - P : u;
	}

	static void pre_w(int n) {
		static int lim = 2;
		n = get_lim(n);
		if (n <= lim)
			return;
		w.resize(n);
		for (int l = lim; l < n; l *= 2) {
			int p = qpow(3, (P - 1) / l / 2, P);
			for (int i = 0; i < l; i += 2) {
				w[l + i] = w[(l + i) / 2];
				w[l + i + 1] = 1ll * w[l + i] * p % P;
			}
		}
		lim = n;
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

	const ll M_1_2 = 1ll * M[0] * M[1];
	const ll inv_1 = qpow(M[0], M[1] - 2, M[1]);
	const ll inv_2 = qpow(M_1_2 % M[2], M[2] - 2, M[2]);
	const ll M12 = M_1_2 % p;

	for (int i = 0; i < m; i++) {
		ll x = NTT<M[1]>::mo(a[1][i] - a[0][i] + M[1]);
		x = x * inv_1 % M[1] * M[0] + a[0][i];
		ll t = NTT<M[2]>::mo(a[2][i] - x % M[2] + M[2]);
		ans[i] = (t * inv_2 % M[2] * M12 + x) % p;
	}
	return ans;
}
