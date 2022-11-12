#include "basic/index.hpp"

#include "poly/ntt-basic.hpp"

using pii = std::pair<int, int>;

struct PolyRelax {
	int now = 0;
	enum : int { M0 = 1024, M = 32 };
	Poly F, G, conv;
	std::map<int, Poly> nf, ng;

	PolyRelax() : F(M0), G(M0), conv(M0) {}

	Poly &getNf(int len) {
		auto &u = nf[len];
		if (u.empty())
			u = F.cut(len).ntt(len);
		return u;
	}

	Poly &getNg(int len) {
		auto &u = ng[len];
		if (u.empty())
			u = G.cut(len).ntt(len);
		return u;
	}

	void set(Z v1, Z v2) {
		F[now] = v1, G[now] = v2;
		conv[now] += G[now] * F[0];
		if (now != 0)
			conv[now] += F[now] * G[0];
		now++;
	}

	Z next() { // return (F * G)[now] - F[0] G[now] - F[now] G[0]
		int len = now & -now, l = now - len;
		if (now < M0) {
			for (int j = (now & -M0) + 1; j < now; ++j)
				conv[now] += G[j] * F[now - j];
		} else if (len == now) {
			conv.redeg(len * 2);
			F.redeg(len * 2);
			G.redeg(len * 2);
			Poly a = getNg(len), &b = getNf(len);
			for (int i = 0; i < len; i++)
				a[i] *= b[i];
			a.intt(len);
			for (int i = len; i < len * 2; i++)
				conv[i] += a[i - len] - conv[i - len];
		} else if (len < M) {
			for (int j = now & -M; j < now; ++j) {
				conv[now] += G[j] * F[now - j] + F[j] * G[now - j];
			}
		} else {
			Poly a = G.cut(len, l), &b = getNf(len * 2);
			Poly c = F.cut(len, l), &d = getNg(len * 2);
			a.ntt(len * 2), c.ntt(len * 2);
			for (int i = 0; i < len * 2; ++i)
				a[i] = a[i] * b[i] + c[i] * d[i];
			a.intt(len * 2);
			for (int i = len; i < len * 2; i++)
				conv[l + i] += a[i];
		}
		return conv[now];
	}
};

Poly relax_inv(Poly F, int m) {
	F.redeg(m);
	PolyRelax X;
	Z iv0 = -F[0].inv();
	X.set(F[0], -iv0);
	for (int i = 1; i < m; i++)
		X.set(F[i], iv0 * (X.next() - F[i] * iv0));
	return X.G.redeg(m);
}

Poly relax_div(Poly H, Poly F, int m) {
	F.redeg(m);
	PolyRelax X;
	Z iv0 = F[0].inv();
	X.set(F[0], iv0 * H[0]);
	for (int i = 1; i < m; i++)
		X.set(F[i], iv0 * (H[i] - X.next()));
	return X.G.redeg(m);
}

Poly relax_exp(Poly F, int m) {
	F.redeg(m);
	PolyRelax X;
	for (int i = 0; i < F.deg(); i++)
		F[i] *= i;
	X.set(F[0], 1);
	for (int i = 1; i < m; i++)
		X.set(F[i], iv[i] * (X.next() + F[i]));
	return X.G.redeg(m);
}

Poly relax_sqrt(Poly F, int m) {
	F.redeg(m);
	PolyRelax X;
	Z iv0 = 1; // F[0].sqrt()
	X.set(iv0, iv0);
	iv0 = (iv0 * 2).inv();
	for (int i = 1; i < m; i++) {
		Z t = (F[i] - X.next()) * iv0;
		X.set(t, t);
	}
	return X.F.redeg(m);
}
