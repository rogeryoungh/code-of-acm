#include "basic/index.hpp"

#include "poly/ntt-basic.hpp"

using pii = std::pair<int, int>;

struct PolySemi {
	int now = 0;
	enum : int { M = 32, B = 16 };
	const Poly &F;
	Poly G, conv;
	std::map<pii, Poly> nf, nr;
	V<int> U;
	PolySemi(const Poly &f) : F(f), G(M), conv(M), U(32, -1) {}
	Poly &getNf(pii p) {
		auto &u = nf[p];
		if (u.empty())
			u = F.cut(p.first, p.second).ntt(p.first);
		return u;
	}
	Poly &getNr(pii p) {
		auto &u = nr[p];
		if (u.empty())
			u = G.cut(p.first, p.second).ntt(p.first * 2);
		return u;
	}
	void set(Z v) {
		G[now] = v;
		conv[now] += G[now] * F[0];
		now++;
	}
	Z next() { // return sum{i in [0, now)} F[i] G[now - i]
		int len = now & -now;
		if (len == now) {
			conv.resize(now * 2);
			G.redeg(now * 2);
		}
		if (len < M) {
			for (int j = now & -M; j < now; ++j)
				conv[now] += G[j] * F[now - j];
		} else {
			int u = std::__lg(len / M) / std::__lg(B);
			int t = ++U[u] % (B - 1);
			len = (1 << (u * std::__lg(B))) * M;
			int l = now - len;
			Poly s(len * 2);
			for (int i = 0; i <= t; i++) {
				Poly &a = getNr({len, l - i * len});
				Poly &b = getNf({len * 2, len * i});
				for (int j = 0; j < len * 2; j++)
					s[j] += a[j] * b[j];
			}
			s.intt(len * 2);
			for (int i = len; i < len * 2; i++)
				conv[l + i] += s[i];
		}
		return conv[now];
	}
};

Poly semi_inv(Poly F, int m) {
	PolySemi X(F.redeg(m));
	Z iv0 = -F[0].inv();
	X.set(-iv0);
	for (int i = 1; i < m; i++) {
		X.set(iv0 * X.next());
	}
	return X.G.redeg(m);
}

Poly semi_inv(Poly H, Poly F, int m) {
	PolySemi X(F.redeg(m));
	Z iv0 = F[0].inv();
	X.set(iv0 * H[0]);
	for (int i = 1; i < m; i++)
		X.set(iv0 * (H[i] - X.next()));
	return X.G.redeg(m);
}

Poly semi_exp(Poly F, int m) {
	for (int i = 0; i < F.size(); i++)
		F[i] *= i;
	PolySemi X(F);
	X.set(1);
	for (int i = 1; i < m; i++)
		X.set(iv[i] * X.next());
	return X.G.redeg(m);
}
