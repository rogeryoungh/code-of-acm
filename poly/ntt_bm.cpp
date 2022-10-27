#include "basic/index.hpp"

#include "poly/ntt-newton.cpp"

Poly bm(const Poly &a) {
	Poly p = {1}, q = {1};
	int l = 0;
	for (int r = 1; r <= a.deg(); r++) {
		Z delta = 0;
		for (int j = 0; j <= l; j++)
			delta += a[r - 1 - j] * p[j];
		q.insert(q.begin(), 0);
		if (delta.v == 0)
			continue;
		Poly t = p;
		if (q.deg() > t.deg())
			t.redeg(q.deg());
		for (int i = 0; i < q.deg(); i++)
			t[i] -= delta * q[i];
		if (2 * l <= r - 1) {
			q = p;
			Z od = delta.inv();
			for (Z &x : q)
				x *= od;
			l = r - l;
		}
		std::swap(p, t);
	}
	assert(p.deg() == l + 1);
	std::reverse(p.begin(), p.end());
	return p;
}

Z mulAt(const Poly &F, const Poly &G, int u) {
	int n = F.size() - 1, m = G.size() - 1;
	int a = std::max(0, u - m), b = std::min(u, n);
	Z ans = 0;
	for (int i = a; i <= b; i++)
		ans += F[i] * G[u - i];
	return ans;
}

// [x^n] F(x)/G(x)
Z divAt(Poly F, Poly G, ll n) {
	int len = std::max(F.deg(), G.deg()), m = get_lim(len);
	for (; n > m; n /= 2) {
		F.ntt(m * 2), G.ntt(m * 2);
		for (int i = 0; i < m * 2; i++)
			F[i] = F[i] * G[i ^ 1];
		for (int i = 0; i < m; i++)
			G[i] = G[i * 2] * G[i * 2 + 1];
		G.redeg(m);
		F.intt(m * 2), G.intt(m);
		for (int i = 0, j = n % 2; i < len; i++, j += 2)
			F[i] = F[j];
		F.redeg(len), G.redeg(len);
	}
	return mulAt(F, G.inv(m), n);
}

// 特征方程 F(x) 和初值 {Ai}，求 An
Z getAn(Poly F, const Poly &A, ll n) {
	std::reverse(F.begin(), F.end());
	assert(F[0].v == 1);
	Poly f = (A * F).cut(A.deg());
	return divAt(f, F, n);
}
