#ifndef ACM_NTT_DIVAT_H
#define ACM_NTT_DIVAT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

Poly& Poly::nttD(int n) {
    auto f = begin();
    copy_n(f, n, f + n), intt(f + n, n);
    for (int i = n; i < n * 2; i++)
        f[i] *= w[i];
    ntt(f + n, n);
}

m32 divAt(Poly F, Poly G, ll n) {
    int len = std::max(F.deg(), G.deg()), m = get_lim(len);
    const int inv_2 = qpow(2, P - 2);
    Poly rt, rt2; {
        rt = Poly{0, 1}.ntt(m * 2);
        rt2 = {1};
        for (int l = 2; l <= m; l <<= 1) {
            for (int j = l - 1; j >= l / 2; j--) {
                rt2.push_back(-rt[j * 2]);
            }
        }
    }
    F.ntt(m), G.ntt(m);
    for (;n > len;n >>= 1) {
        F.nttD(m), G.nttD(m);
        for (int i = 0; i < m * 2; i++) {
            F[i] *= G[i ^ 1];
        }
        if (n & 1) {
            for (int j = 0; j < m; j++)
                F[j] = rt2[j] * (F[j * 2] - F[j * 2 + 1]) * inv_2;
        } else {
            for (int i = 0, j = 0; i < m * 2; i+= 2, j++)
                F[j] = (F[j * 2] + F[j * 2 + 1]) * inv_2;
        }
        for (int i = 0; i < m; i++) {
            G[i] = G[i * 2] * G[i * 2 + 1];
        }
    }
    F.redeg(m).intt(m), G.redeg(m).intt(m);
    return mulAt(F, G.inv(), n);
}

m32 getAn(Poly F, const Poly &A, ll n, int k) {
    F = Poly{1} - F;
    Poly f = (A * F).cut(k);
    return divAt(f, F, n);
}

#endif
