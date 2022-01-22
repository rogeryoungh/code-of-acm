#ifndef ACM_NTT_CDQ_H
#define ACM_NTT_CDQ_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/cache/0.hpp"

struct PolyCDQ {
    int deg, now = 1;
    const int M = 64;
    const Poly &F;
    Poly &G;
    NttCache<int> nf;

    PolyCDQ(const Poly &f, Poly &g) : F(f), G(g) {
        deg = F.size();
        nf.exec = [&](int len) {
            return F.cut(len).ntt(len);
        };
    }

    m32 next() {
        int len = now & -now, l = now - len;
        if (len < M) {
            for (int j = now & -M; j < now; ++j)
                G[now] += G[j] * F[now - j];
        } else {
            Poly a = G.cut(len, l).ntt(len * 2), &b = nf.get(len * 2);
            for (int i = 0; i < len * 2; i++)
                a[i] *= b[i];
            a.intt(len * 2);
            for (int i = len; i < std::min(len * 2, deg - l); i++)
                G[l + i] += a[i];
        }
        return G[now++];
    }
};

#endif