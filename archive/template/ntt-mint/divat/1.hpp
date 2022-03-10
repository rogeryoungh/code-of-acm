#ifndef ACM_NTT_DIVAT_H
#define ACM_NTT_DIVAT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"
#include "template/ntt-mint/inv/0.hpp"

Poly& Poly::nttD(int n) {
    auto f = begin();
    copy_n(f, n, f + n), intt(f + n, n);
    for (int i = n; i < n * 2; i++)
        f[i] *= w[i];
    ntt(f + n, n);
}

m32 divAt(Poly F, Poly G, ll n) {
    int len = max(F.deg(), G.deg()), m = get_lim(len);
    G.ntt(m);
    for (; n > len; n >>= 1) {
        F.ntt(m * 2), G.nttD(m);
        for (int i = 0; i < m * 2; i++)
            F[i] = F[i] * G[i ^ 1];
        for (int i = 0; i < m; i++)
            G[i] = G[i * 2] * G[i * 2 + 1];
        F.intt(m * 2);
        for (int i = 0, j = n & 1; i < len; i++, j += 2)
            F[i] = F[j];
        F.redeg(len);
    }
    G.redeg(m).intt(m);
    return mulAt(F, G.inv(), n);
}

m32 getAn(Poly F, const Poly &A, ll n, int k) {
    for (auto &i : F)
        i = -i;
    F[0] += 1;
    Poly f = (A * F).cut(k);
    return divAt(move(f), move(F), n);
}

#endif
