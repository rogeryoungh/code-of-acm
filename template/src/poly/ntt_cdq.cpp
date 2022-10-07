#include "basic/index.hpp"

#include "poly/ntt-newton.cpp"

struct PolyCDQ {
	int now = 0;
	const int M = 32;
	Poly &F, &G, conv;
	std::map<int, Poly> nf;

	PolyCDQ(Poly &f, Poly &g) : F(f), G(g), conv(M) {}

	Z next() { // return  (F * G)[now] - F[0] G[now]
		conv[now] += G[now] * F[0];
		now++;
		int len = now & -now, l = now - len;
		if (len < M) {
			for (int j = now & -M; j < now; ++j)
				conv[now] += G[j] * F[now - j];
		} else {
			Poly a = G.cut(len, l).ntt(len * 2), &b = nf[len];
			if (l == 0) {
				b = F.cut(len * 2).ntt(len * 2);
				conv.redeg(now * 2);
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

Poly cdq_inv(Poly F, int m) {
	Poly G(m);
	PolyCDQ X(F.redeg(m), G);
	Z iv0 = -F[0].inv();
	G[0] = -iv0;
	for (int i = 1; i < m; i++)
		G[i] = iv0 * X.next();
	return G;
}

Poly cdq_div(Poly H, Poly F, int m) {
	Poly G(m);
	PolyCDQ X(F.redeg(m), G);
	Z iv = F[0].inv();
	G[0] = iv * H[0];
	for (int i = 1; i < m; i++)
		G[i] = iv * (H[i] - X.next());
	return G;
}

Poly cdq_exp(Poly F, int m) {
	Poly G(m);
	for (int i = 0; i < F.size(); i++)
		F[i] *= i;
	PolyCDQ X(F.redeg(m), G);
	G[0] = 1;
	for (int i = 1; i < m; i++)
		G[i] = iv[i] * X.next();
	return G;
}
