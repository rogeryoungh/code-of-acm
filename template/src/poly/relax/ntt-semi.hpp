#include "basic/index.hpp"

#include "poly/ntt-basic.hpp"

struct PolySemi {
	int now = 0;
	enum : int { M = 32 };
	const Poly &F;
	Poly G, conv;
	std::map<int, Poly> nf;
	PolySemi(const Poly &f) : F(f), G(M), conv(M) {}
	void set(Z v) {
		G[now] = v;
		conv[now] += G[now] * F[0];
		now++;
	}
	Z next() { // return  (F * G)[now] - F[0] G[now]
		int len = now & -now, l = now - len;
		if (len < M) {
			for (int j = now & -M; j < now; ++j)
				conv[now] += G[j] * F[now - j];
		} else {
			Poly a = G.cut(len, l).ntt(len * 2), &b = nf[len];
			if (l == 0) {
				b = F.cut(len * 2).ntt(len * 2);
				conv.redeg(now * 2);
				G.redeg(now * 2);
			}
			for (int i = 0; i < len * 2; i++)
				a[i] *= b[i];
			a.intt(len * 2);
			for (int i = len; i < len * 2; i++)
				conv[l + i] += a[i];
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

Poly semi_div(Poly H, Poly F, int m) {
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
