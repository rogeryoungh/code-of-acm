#ifndef ACM_NTT_ONLINE_CONVOLUION_H
#define ACM_NTT_ONLINE_CONVOLUION_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/cache/0.hpp"

struct PolyOC {
    int now = 0;
    const int M0 = 1024, M = 32;
    const Poly &F, &G;
    Poly conv;
    NttCache<int> nf, ng;

    PolyOC(const Poly &f, const Poly &g) : F(f), G(g) {
        conv.resize(M0);
        nf.exec = [&](int len) {
            return F.cut(len).ntt(len);
        };
        ng.exec = [&](int len) {
            return G.cut(len).ntt(len);
        };
    }

    m32 next() { // return sum{i in [1, now)} F[i] G[now - i]
        conv[now] += G[now] * F[0];
        if (now != 0)
            conv[now] += F[now] * G[0];
        now++;
        int len = now & -now, l = now - len;
        if (now < M0) {
            for (int j = (now & -M0) + 1; j < now; ++j)
                conv[now] += G[j] * F[now - j];
        } else if (len == now) {
            conv.resize(len * 2);
            Poly a = ng.get(len), &b = nf.get(len);
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
            Poly a = G.cut(len, l), &b = nf.get(len * 2);
            Poly c = F.cut(len, l), &d = ng.get(len * 2);
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

#endif
