#ifndef ACM_NTT_INT_CDQ_H
#define ACM_NTT_INT_CDQ_H

#include "template/ntt-int/fps/O.hpp"

struct PolyCDQ {
    int now = 0;
    const int M = 32;
    Poly &F, &G, conv;
    std::map<int, Poly> nf;

    PolyCDQ(Poly &f, Poly &g) : F(f), G(g), conv(M) {}

    int next() { // return  (F * G)[now] - F[0] G[now]
        conv[now] = (conv[now] + 1ll * G[now] * F[0]) % P;
        now++;
        int len = now & -now, l = now - len;
        if (len < M) {
            u64 s = 0;
            for (int j = now & -M; j < now; ++j) {
                s += 1ll * G[j] * F[now - j] % P;
            }
            conv[now] = (conv[now] + s) % P;
        } else {
            Poly a = G.cut(len, l).ntt(len * 2), &b = nf[len];
            if (l == 0)
                b = F.cut(len * 2).ntt(len * 2), conv.redeg(now * 2);
            for (int i = 0; i < len * 2; i++)
                a[i] = 1ll * a[i] * b[i] % P;
            a.intt(len * 2);
            for (int i = len; i < len * 2; i++)
                conv[l + i] = mo(a[i] + conv[l + i]);
        }
        return conv[now];
    }
};

Poly cdq_inv(Poly F, int m) {
    Poly G(m);
    PolyCDQ X(F.redeg(m), G);
    int iv = P - qpow(F[0]);
    G[0] = mo(P - iv);
    for (int i = 1; i < m; i++)
        G[i] = 1ll * iv * X.next() % P;
    return G;
}

Poly cdq_div(Poly H, Poly F, int m) {
    Poly G(m);
    PolyCDQ X(F.redeg(m), G);
    int iv = qpow(G[0]);
    G[0] = 1ll * iv * H[0] % P;
    for (int i = 1; i < m; i++)
        G[i] = 1ll * iv * (F[i] - X.next() + P) % P;
    return G;
}

Poly cdq_exp(Poly F, int m) {
    Poly G(m);
    pre_inv(m);
    for (int i = 0; i < F.size(); i++)
        F[i] = 1ll * i * F[i] % P;
    PolyCDQ X(F.redeg(m), G);
    G[0] = 1;
    for (int i = 1; i < m; i++)
        G[i] = 1ll * Inv[i] * X.next() % P;
    return G;
}

#endif