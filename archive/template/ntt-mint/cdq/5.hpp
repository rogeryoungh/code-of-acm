#ifndef ACM_NTT_CDQ_H
#define ACM_NTT_CDQ_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

struct PolyCDQ {
    int now = 0;
    const int M = 64;
    const Poly &F, &G;
    Poly conv;
    std::map<int, Poly> nf;

    PolyCDQ(const Poly &f, const Poly &g) : F(f), G(g) {
        conv.resize(M);
    }

    m32 next() { // return  (F * G)[now] - F[0] G[now]
        conv[now] += G[now] * F[0], now++;
        int len = now & -now, l = now - len;
        if (len < M) {
            for (int j = now & -M; j < now; ++j)
                conv[now] += G[j] * F[now - j];
        } else {
            Poly a = G.cut(len, l), &b = nf[len];
            if (l == 0) // b.empty()
                b = F.cut(len * 2), conv.resize(now * 2);
            mul(a, b, len * 2);
            for (int i = len; i < len * 2; i++)
                conv[l + i] += a[i];
        }
        return conv[now];
    }
};

#endif